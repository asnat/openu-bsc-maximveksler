#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <stdlib.h>

#include "assemblyLANG.h"
#include "asmInstruction.h"
#include "codeSegmentMgr.h"
#include "dataSegmentMgr.h"
#include "errorHandler.h"
#include "asmCommands.h"
#include "constants.h"
#include "label.h"
#include "hash.h"

#define OP_SRC_CBIT(y) (y) /* Operand Source Check BIT macro */
#define OP_DST_CBIT(y) ((y) << 8) /* Operand Destination Check BIT macro */

#define OP_SRC_CBIT_EXTRACT(y) ((y) & (0xFF)) /* Operand Source Check BIT macro */
#define OP_DST_CBIT_EXTRACT(y) ((y) & (0xFF << 8)) /* Operand Source Check BIT macro */

#define NUMBER_DATA_TOKEN ", \t"

#define ASM_COMMANDS_DEBUG 0


_bool storeToCodeSegment(
        unsigned short dstRgstrCode,
        unsigned short dstAddrTypeCode,
        unsigned short srcRgstrCode,
        unsigned short srcAddrTypeCode,
        unsigned short instCode) {

    unsigned short instruction = 0;

    instruction = dstRgstrCode;
    instruction |= (unsigned short) (dstAddrTypeCode << 3);
    instruction |= (unsigned short) (srcRgstrCode << 6);
    instruction |= (unsigned short) (srcAddrTypeCode << 9);
    instruction |= (unsigned short) (instCode << 12);

    #if ASM_COMMANDS_DEBUG
        printf("Storing: %X into data segment\n", instruction);
    #endif

    if (instruction == 0)
        storeCode(instruction, RELOCATBLE);
    else
        storeCode(instruction, ABSOLUTE);

    return TRUE;
}

static _bool processCommand(AsmInstruction asmInstruction,
        unsigned short commandCode,
        unsigned int supportedAddressing) {

    unsigned short dstRgstrCode = 0;
    unsigned short dstAddrTypeCode = 0;
    unsigned short srcRgstrCode = 0;
    unsigned short srcAddrTypeCode = 0;

    _bool __reserve_dst_label_space = FALSE;
    _bool __reserve_src_label_space = FALSE;
    
    if(! (OP_SRC_CBIT_EXTRACT(supportedAddressing) & OP_SRC_CBIT(asmInstruction->instruction->INST.srcOPType))) {
        /* Check that the first operand type supplied is valid */
        handleError(WRONG_ADDRESSING_TYPE, "Source operand is illigal for instruction");
        return FALSE;
    }

    if(! (OP_DST_CBIT_EXTRACT(supportedAddressing) & OP_DST_CBIT(asmInstruction->instruction->INST.dstOPType))) {
        /* Check that the second operand type supplied is valid */
        handleError(WRONG_ADDRESSING_TYPE, "Destination operand is illigal for instruction");
        return FALSE;
    }

    
    /* Reaching here we know that our supplied operand for instruction are indeed valid. YAY! */


    /* Translate addressing operand code from ENUM representation to asm instruction code */
    switch (OP_SRC_CBIT(asmInstruction->instruction->INST.srcOPType)) {
        case OP_SRC_CBIT(IMMIDIATE):
            srcAddrTypeCode = ASM_LANG_ADDR_IMMIDIATE;
            __reserve_src_label_space = TRUE;
            break;
        case OP_SRC_CBIT(DIRECT):
            srcAddrTypeCode = ASM_LANG_ADDR_DIRECT;
            __reserve_src_label_space = TRUE;
            break;
        case OP_SRC_CBIT(INDIRECT):
            srcAddrTypeCode = ASM_LANG_ADDR_INDIRECT;
            __reserve_src_label_space = TRUE;
            break;
        case OP_SRC_CBIT(REGISTER):
            srcAddrTypeCode = ASM_LANG_ADDR_REGISTER;
            /* Calculate src register code if we are in REGISTER addressing */
            srcRgstrCode = (unsigned short) (asmInstruction->instruction->INST.srcOP[1] - 48);
            break;
        case OP_SRC_CBIT(NO_OP):
            srcAddrTypeCode = ASM_LANG_ADDR_NO_OP;
            break;
        /* at this stage srcOPType is ensured to be valid, so no need for error catching default */
    }

    switch (OP_DST_CBIT(asmInstruction->instruction->INST.dstOPType)) {
        case OP_DST_CBIT(IMMIDIATE):
            dstAddrTypeCode = ASM_LANG_ADDR_IMMIDIATE;
            __reserve_dst_label_space = TRUE;
            break;
        case OP_DST_CBIT(DIRECT):
            dstAddrTypeCode = ASM_LANG_ADDR_DIRECT;
            __reserve_dst_label_space = TRUE;
            break;
        case OP_DST_CBIT(INDIRECT):
            dstAddrTypeCode = ASM_LANG_ADDR_INDIRECT;
            __reserve_dst_label_space = TRUE;
            break;
        case OP_DST_CBIT(REGISTER):
            dstAddrTypeCode = ASM_LANG_ADDR_REGISTER;
            /* Calculate dst register code if we are in REGISTER addressing */
            dstRgstrCode = (unsigned short) (asmInstruction->instruction->INST.dstOP[1] - 48);
            break;
        case OP_DST_CBIT(NO_OP):
            dstAddrTypeCode = ASM_LANG_ADDR_NO_OP;
            break;
        /* at this stage dstOPType is ensured to be valid, so no need for error catching default */
    }

    /* We want to add label reference to the location where the assembly code
     * will be written to.
     */
    if(asmInstruction->label != NULL) {
        if (addLabel(asmInstruction->label, RELOCATBLE, getIC()) == FALSE) {
            handleError(LABEL_ADDING_FAILURE, asmInstruction->label);
            return FALSE;
        }
    }


    /* Finally after passing all check and translations we are ready to store the asm instruction */
    storeToCodeSegment(
        /*unsigned short dstRgstrCode*/     dstRgstrCode,
        /*unsigned short dstAddrTypeCode*/  dstAddrTypeCode,
        /*unsigned short srcRgstrCode*/     srcRgstrCode  ,
        /*unsigned short srcAddrTypeCode*/  srcAddrTypeCode,
        /*unsigned short instCode*/         commandCode);

    
    /* Possibly make some more calls, to reservce space for later label filling logic... */
    if(__reserve_dst_label_space) {
        storeToCodeSegment(0, 0, 0, 0, 0);
    }

    if(__reserve_src_label_space) {
        storeToCodeSegment(0, 0, 0, 0, 0);
    }

    return TRUE;
}

static _bool processDataNumber(AsmInstruction asmInstruction) {
    char * pch;
    unsigned int i;
    int number;
    _bool labelStored = FALSE;
    

    pch = strtok (asmInstruction->instruction->DATA.decData,  NUMBER_DATA_TOKEN);
    if(pch == NULL) {
        /* declaration data contained nothing but delimiters, this is obviously
         a no-no*/

        handleError(DATA_DECLARATION_EMPTY, NULL);
        return FALSE;
    }

    while(pch != NULL) {
        i = 0;

        if(pch[i] != '+' && pch[i] != '-' && !isdigit(pch[i])) {
            /* We have something that is not a number */
            /* TODO: ERROR NOT_A_VALID_NUMBER */
            return FALSE;
        }

        while(isdigit(pch[++i])) /* Consume all digits */
            ;

        if(pch[i] != '\0') { /* After we finished consuming digits there should be nothing left */
            /* We have something that is not a number */
            /* TODO: ERROR NOT_A_VALID_NUMBER */
            return FALSE;
        }

        number = atoi(pch);

        if(number >= 0) {
            if(number > SHRT_MAX) {
                /* We found a number that is too large to fit into 16bit space */
                /* TODO: ERROR NUMBER TOO BIG */
                return FALSE;
            }
        } else {
            if(number < SHRT_MIN) {
                /* We found a number that is too small to fit into 16bit space */
                /* TODO: ERROR NUMBER TOO SMALL */
                return FALSE;
            }
        }

        if(!labelStored && asmInstruction->label != NULL) {
            /* We want to add label reference to the location where the assembly data
             * will be written to.
             */
            if (addLabel(asmInstruction->label, RELOCATBLE, getDC()) == FALSE) {
                handleError(LABEL_ADDING_FAILURE, asmInstruction->label);
                return FALSE;
            }

            labelStored = TRUE;
        }

        /* Finnally store the data in the data segment */
        storeData((unsigned short) number);

        /* And progress to next value */
        pch = strtok(NULL, NUMBER_DATA_TOKEN);
    }

    return TRUE;
}

static _bool processDataString(AsmInstruction asmInstruction) {
    unsigned int i = 0;
    unsigned int to;
    char* pos;

    pos = asmInstruction->instruction->DATA.decData;

    /* Input validation */
    if(pos[i] != '"') { /* Check that the first char is " */
        /* TODO: Error not valid string definition */
        return FALSE;
    }

    while((pos[++i])) /* Consume all chars up to null */
        ;

    if((pos[i-1]) != '"') { /* Check that the last char is " */
        /* TODO: Error not valid string definition */
        return FALSE;
    }

    if(asmInstruction->label != NULL) {
        /* We want to add label reference to the location where the assembly data
         * will be written to.
         */
        if (addLabel(asmInstruction->label, RELOCATBLE, getDC()) == FALSE) {
            handleError(LABEL_ADDING_FAILURE, asmInstruction->label);
            return FALSE;
        }
    }

    /* Store each char in it's own line in data segment */
    to = i - 1;
    for(i = 1; i < to; i++) {
        storeData((unsigned short) pos[i]);
    }

    storeData((unsigned short) '\0'); /* Store the line terminaltion char */

    return TRUE;
}

/* Add reference for an external label */
_bool processExternal(AsmInstruction asmInstruction) {
    if(asmInstruction->instruction->EXTERN.referenceName == NULL) {
        handleError(MISSING_EXTERN_REFERENCE, NULL);
        return FALSE;
    }

    if (addLabel(asmInstruction->instruction->EXTERN.referenceName, EXTERNAL, /*meaning less, external */ 0) == FALSE) {
        handleError(LABEL_ADDING_FAILURE, asmInstruction->instruction->EXTERN.referenceName);
        return FALSE;
    }

    return TRUE;
}


/* #############################################################
 * ###### Assembly language implementation #####################
 * #############################################################
 */

static asm_cmd_struct cmdTable[] = {
    {"mov", ASM_LANG_CMD_MOV_CODE,
            OP_SRC_CBIT(IMMIDIATE) | OP_SRC_CBIT(DIRECT) | OP_SRC_CBIT(INDIRECT) | OP_SRC_CBIT(REGISTER)
            | OP_DST_CBIT(DIRECT) | OP_DST_CBIT(INDIRECT) | OP_DST_CBIT(REGISTER)
    },
    {"cmp", ASM_LANG_CMD_CMP_CODE,
            OP_SRC_CBIT(IMMIDIATE) | OP_SRC_CBIT(DIRECT) | OP_SRC_CBIT(INDIRECT) | OP_SRC_CBIT(REGISTER)
            | OP_DST_CBIT(IMMIDIATE) | OP_DST_CBIT(DIRECT) | OP_DST_CBIT(INDIRECT) | OP_DST_CBIT(REGISTER)
    },
    {"add", ASM_LANG_CMD_ADD_CODE,
            OP_SRC_CBIT(IMMIDIATE) | OP_SRC_CBIT(DIRECT) | OP_SRC_CBIT(INDIRECT) | OP_SRC_CBIT(REGISTER)
            | OP_DST_CBIT(DIRECT) | OP_DST_CBIT(INDIRECT) | OP_DST_CBIT(REGISTER)
    },
    {"sub", ASM_LANG_CMD_SUB_CODE,
            OP_SRC_CBIT(IMMIDIATE) | OP_SRC_CBIT(DIRECT) | OP_SRC_CBIT(INDIRECT) | OP_SRC_CBIT(REGISTER)
            | OP_DST_CBIT(DIRECT) | OP_DST_CBIT(INDIRECT) | OP_DST_CBIT(REGISTER)
    },
    {"mul", ASM_LANG_CMD_MUL_CODE,
            OP_SRC_CBIT(IMMIDIATE) | OP_SRC_CBIT(DIRECT) | OP_SRC_CBIT(INDIRECT) | OP_SRC_CBIT(REGISTER)
            | OP_DST_CBIT(DIRECT) | OP_DST_CBIT(INDIRECT) | OP_DST_CBIT(REGISTER)
    },
    {"div", ASM_LANG_CMD_DIV_CODE,
            OP_SRC_CBIT(IMMIDIATE) | OP_SRC_CBIT(DIRECT) | OP_SRC_CBIT(INDIRECT) | OP_SRC_CBIT(REGISTER)
            | OP_DST_CBIT(DIRECT) | OP_DST_CBIT(INDIRECT) | OP_DST_CBIT(REGISTER)
    },
    {"lea", ASM_LANG_CMD_LEA_CODE,
            OP_SRC_CBIT(DIRECT)
            | OP_DST_CBIT(DIRECT) | OP_DST_CBIT(INDIRECT) | OP_DST_CBIT(REGISTER)
    },
    {"inc", ASM_LANG_CMD_INC_CODE,
            OP_SRC_CBIT(NO_OP)
            | OP_DST_CBIT(DIRECT) | OP_DST_CBIT(INDIRECT) | OP_DST_CBIT(REGISTER)
    },
    {"dec", ASM_LANG_CMD_DEC_CODE,
            OP_SRC_CBIT(NO_OP)
            | OP_DST_CBIT(DIRECT) | OP_DST_CBIT(INDIRECT) | OP_DST_CBIT(REGISTER)
    },
    {"jmp", ASM_LANG_CMD_JMP_CODE,
            OP_SRC_CBIT(NO_OP)
            | OP_DST_CBIT(DIRECT) | OP_DST_CBIT(INDIRECT)
    },
    {"bne", ASM_LANG_CMD_BNE_CODE,
            OP_SRC_CBIT(NO_OP)
            | OP_DST_CBIT(DIRECT) | OP_DST_CBIT(INDIRECT)
    },
    {"red", ASM_LANG_CMD_RED_CODE,
            OP_SRC_CBIT(NO_OP)
            | OP_DST_CBIT(DIRECT) | OP_DST_CBIT(INDIRECT) | OP_DST_CBIT(REGISTER)
    },
    {"prn", ASM_LANG_CMD_PRN_CODE,
            OP_SRC_CBIT(NO_OP)
            | OP_DST_CBIT(IMMIDIATE) | OP_DST_CBIT(DIRECT) | OP_DST_CBIT(INDIRECT) | OP_DST_CBIT(REGISTER)
    },
    {"jsr", ASM_LANG_CMD_JSR_CODE,
            OP_SRC_CBIT(NO_OP)
            | OP_DST_CBIT(DIRECT) | OP_DST_CBIT(INDIRECT)
    },
    {"rts", ASM_LANG_CMD_RTS_CODE,
            OP_SRC_CBIT(NO_OP)
            | OP_DST_CBIT(NO_OP)
    },
    {"hlt", ASM_LANG_CMD_HLT_CODE,
            OP_SRC_CBIT(NO_OP)
            | OP_DST_CBIT(NO_OP)
    },
    {NULL, (unsigned short)((unsigned int)NULL), (unsigned int)NULL}
};

void process(AsmInstruction asmLineInstruction) {
    asm_cmd_struct *asm_cmd_struct_handler;
    const char *handlerName;

    if(asmLineInstruction->instructionType == INST) {
        handlerName = asmLineInstruction->instruction->INST.command;

        /* Dynamically seek (&find) correct fuction to call
         * We stop either on dynaFuncHandler->function_name == NULL
         * or on match strcmp(pch,  dynaFuncHandler->function_name) == 0
         */
        for(asm_cmd_struct_handler = cmdTable;  asm_cmd_struct_handler->function_name && strcmp(handlerName,  asm_cmd_struct_handler->function_name); asm_cmd_struct_handler++)
            ;

        /* If we have found a function at this name */
        if(asm_cmd_struct_handler->function_name) {
            #if ASM_COMMANDS_DEBUG
                printf("asmCommands.process: function_name = %s\n", asm_cmd_struct_handler->function_name);
            #endif
            /* We want to pass the next location after the function name in the general user input string */
            processCommand(asmLineInstruction, asm_cmd_struct_handler->commandCode, asm_cmd_struct_handler->supportedAddressingBitmap);
        } else {
            handleError(NO_SUCH_ASSEMBLY_COMMAND, handlerName);

        }
    } else if (asmLineInstruction->instructionType == DATA) {
        if(asmLineInstruction->instruction->DATA.dataType == DataType_DATA) {
            processDataNumber(asmLineInstruction);
        } else if (asmLineInstruction->instruction->DATA.dataType == DataType_STRING) {
            processDataString(asmLineInstruction);
        }
    } else if(asmLineInstruction->instructionType == EXTERN) {
        processExternal(asmLineInstruction);
    }
}