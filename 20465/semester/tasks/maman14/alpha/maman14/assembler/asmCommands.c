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


/* #############################################################
 * ###### Assembly language implementation #####################
 * #############################################################
 */

/* This array holds for each command whata addressing types are allowed for what openrand */
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

/* Valid input for short, and if valid write into provided int pointer, returns
 * FALSE if not valid */
static _bool processShortNumber(const char* source, int* number) {
    unsigned int i;

    i = 0;

    if(*source != '+' && *source != '-' && !isdigit(*source)) {
        /* We have something that is not a number */
        /* TODO: ERROR NOT_A_VALID_NUMBER */
        return FALSE;
    }

    while(isdigit(source[++i])) /* Consume all digits */
        ;

    if(source[i] != '\0') { /* After we finished consuming digits there should be nothing left */
        /* We have something that is not a number */
        /* TODO: ERROR NOT_A_VALID_NUMBER */
        return FALSE;
    }

    *number = atoi(source);

    if(*number >= 0) {
        if(*number > SHRT_MAX) {
            /* We found a number that is too large to fit into 16bit space */
            /* TODO: ERROR NUMBER TOO BIG */
            return FALSE;
        }
    } else {
        if(*number < SHRT_MIN) {
            /* We found a number that is too small to fit into 16bit space */
            /* TODO: ERROR NUMBER TOO SMALL */
            return FALSE;
        }
    }

    return TRUE;
}

/* generate assembly translated binary to code segment for phase 2 */
static unsigned short generateCode(
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

    return instruction;
}

/* Utility method to add lable to hash manager */
static _bool addLabelToHash(char* label, LinkerAddress linkerAddress, unsigned int offset, hashSegmentType segment) {
    asm_cmd_struct *asm_cmd_struct_handler;
    for(asm_cmd_struct_handler = cmdTable;  asm_cmd_struct_handler->function_name && strcmp(label,  asm_cmd_struct_handler->function_name); asm_cmd_struct_handler++)
        ;

    /* Check that label name is not a reserved commmand name */
    if(asm_cmd_struct_handler->function_name) {
        /* We found a command by this label, this is an error! */
        handleError(RESERVED_WORD, label);
        return FALSE;
    }

    /* Check that label name is not a reserved register name */
    if(*label == 'r' && (*(label+1) >= '0' || *(label+1) <= '7') &&  *(label+2) == '\0') {
        /* We found a command by this label, this is an error! */
        handleError(RESERVED_WORD, label);
        return FALSE;
    }

    if(addLabel(label, linkerAddress, offset, segment))
        return TRUE;
    else
        return FALSE;
}

/* Get AsmInstruction and translate it to assembly code */
static _bool processCommand(AsmInstruction asmInstruction,
        unsigned short commandCode,
        unsigned int supportedAddressing) {

    unsigned short dstRgstrCode = 0;
    unsigned short dstAddrTypeCode = 0;
    unsigned short srcRgstrCode = 0;
    unsigned short srcAddrTypeCode = 0;




    unsigned short commandBITS = 0;

    _bool __add_dst_operand = FALSE;
    int dstOperandBITS = 0;
    LinkerAddress dstOperandLinkerAddress;

    _bool __add_src_operand = FALSE;
    int srcOperandBITS = 0;
    LinkerAddress srcOperandLinkerAddress;

    
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
            __add_src_operand = TRUE;
            srcOperandLinkerAddress = ABSOLUTE;
            if(!processShortNumber(asmInstruction->instruction->INST.srcOP, &srcOperandBITS)) {
                handleError(INVALID_DECLARATION_FORMAT, asmInstruction->instruction->INST.srcOP);
            }
            
            break;
        case OP_SRC_CBIT(DIRECT):
            srcAddrTypeCode = ASM_LANG_ADDR_DIRECT;
            __add_src_operand = TRUE;
            srcOperandLinkerAddress = RELOCATBLE;
            srcOperandBITS = 0;
            
            break;
        case OP_SRC_CBIT(INDIRECT):
            srcAddrTypeCode = ASM_LANG_ADDR_INDIRECT;
            __add_src_operand = TRUE;
            srcOperandLinkerAddress = RELOCATBLE;
            srcOperandBITS = 0;

            break;
        case OP_SRC_CBIT(REGISTER):
            srcAddrTypeCode = ASM_LANG_ADDR_REGISTER;
            __add_src_operand = FALSE;
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
            __add_dst_operand = TRUE;
            dstOperandLinkerAddress = ABSOLUTE;
            if(!processShortNumber(asmInstruction->instruction->INST.dstOP, &dstOperandBITS)) {
                handleError(INVALID_DECLARATION_FORMAT, asmInstruction->instruction->INST.dstOP);
            }

            break;
        case OP_DST_CBIT(DIRECT):
            dstAddrTypeCode = ASM_LANG_ADDR_DIRECT;
            __add_dst_operand = TRUE;
            dstOperandLinkerAddress = RELOCATBLE;
            dstOperandBITS = 0;

            break;
        case OP_DST_CBIT(INDIRECT):
            dstAddrTypeCode = ASM_LANG_ADDR_INDIRECT;
            __add_dst_operand = TRUE;
            dstOperandLinkerAddress = RELOCATBLE;
            dstOperandBITS = 0;

            break;
        case OP_DST_CBIT(REGISTER):
            dstAddrTypeCode = ASM_LANG_ADDR_REGISTER;
            __add_dst_operand = FALSE;

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
        if (addLabelToHash(asmInstruction->label, /* Should be relocatable */ RELOCATBLE, getIC(), CODE_SEG) == FALSE) {
            handleError(LABEL_ADDING_FAILURE, asmInstruction->label);
            return FALSE;
        }
    }

    /* Finally after passing all check and translations we are ready to store the asm instruction */
    commandBITS = generateCode(
        /*unsigned short dstRgstrCode*/     dstRgstrCode,
        /*unsigned short dstAddrTypeCode*/  dstAddrTypeCode,
        /*unsigned short srcRgstrCode*/     srcRgstrCode  ,
        /*unsigned short srcAddrTypeCode*/  srcAddrTypeCode,
        /*unsigned short instCode*/         commandCode);


    storeCode(commandBITS, ABSOLUTE);
    
    /* Possibly make some more calls, to reservce space for later label filling logic... */
    if(__add_src_operand) {
        storeCode(srcOperandBITS, srcOperandLinkerAddress);
    }

    if(__add_dst_operand) {
        storeCode(dstOperandBITS, dstOperandLinkerAddress);
    }

    return TRUE;
}


static _bool processDataNumber(AsmInstruction asmInstruction) {
    char * pch;
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

        if(!processShortNumber(pch, &number))
            return FALSE;
        
        if(!labelStored && asmInstruction->label != NULL) {
            /* We want to add label reference to the location where the assembly data
             * will be written to.
             */
            if (addLabelToHash(asmInstruction->label, RELOCATBLE, getDC(), DATA_SEG) == FALSE) {
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
        if (addLabelToHash(asmInstruction->label, RELOCATBLE, getDC(), DATA_SEG) == FALSE) {
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

    if (addLabelToHash(asmInstruction->instruction->EXTERN.referenceName, EXTERNAL, 
            /*meaningless because label is external */ 0, EXTERN_SEG) == FALSE) {
        handleError(LABEL_ADDING_FAILURE, asmInstruction->instruction->EXTERN.referenceName);
        return FALSE;
    }

    return TRUE;
}



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
            if(!processDataNumber(asmLineInstruction)) {
                handleError(INVALID_DECLARATION_FORMAT, "DataType_DATA");
            }
        } else if (asmLineInstruction->instruction->DATA.dataType == DataType_STRING) {
            if(!processDataString(asmLineInstruction)) {
                handleError(INVALID_DECLARATION_FORMAT, "DataType_STRING");
            }
        }
    } else if(asmLineInstruction->instructionType == EXTERN) {
        processExternal(asmLineInstruction);
    }
}