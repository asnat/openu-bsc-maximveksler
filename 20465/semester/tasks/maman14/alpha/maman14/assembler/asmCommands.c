#include <stdio.h>

#include "assemblyLANG.h"
#include "asmInstruction.h"
#include "codeSegmentMgr.h"
#include "errorHandler.h"
#include "asmCommands.h"
#include "constants.h"

#define OP_SRC_CBIT(y) (y) /* Operand Source Check BIT macro */
#define OP_DST_CBIT(y) ((y) << 8) /* Operand Destination Check BIT macro */

#define OP_SRC_CBIT_EXTRACT(y) ((y) & (0xFF)) /* Operand Source Check BIT macro */
#define OP_DST_CBIT_EXTRACT(y) ((y) & (0xFF << 8)) /* Operand Source Check BIT macro */

#define DEBUG 1


static unsigned short storeToCodeSegment(
        unsigned short dstRgstrCode,
        unsigned short dstAddrTypeCode,
        unsigned short srcRgstrCode,
        unsigned short srcAddrTypeCode,
        unsigned short instCode) {

    unsigned short instruction = 0;

    instruction = dstRgstrCode;
    instruction |= (dstAddrTypeCode << 3);
    instruction |= (srcRgstrCode << 6);
    instruction |= (srcAddrTypeCode << 9);
    instruction |= (instCode << 12);

    #if DEBUG
        printf("Storing: %X into data segment\n", instruction);
    #endif
        
    storeData(instruction);
}

_bool processCommand(AsmInstruction asmInstruction,
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
        handleError(asmInstruction->lineNumber, WRONG_ADDRESSING_TYPE, "Source operand is illigal for instruction", asmInstruction->_log_unparsedAssemblyLine);
        return FALSE;
    }

    if(! (OP_DST_CBIT_EXTRACT(supportedAddressing) & OP_DST_CBIT(asmInstruction->instruction->INST.dstOPType))) {
        handleError(asmInstruction->lineNumber, WRONG_ADDRESSING_TYPE, "Destination operand is illigal for instruction", asmInstruction->_log_unparsedAssemblyLine);
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
            srcRgstrCode = asmInstruction->instruction->INST.srcOP[1] - 48;
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
            dstRgstrCode = asmInstruction->instruction->INST.dstOP[1] - 48;
            break;
        case OP_DST_CBIT(NO_OP):
            dstAddrTypeCode = ASM_LANG_ADDR_NO_OP;
            break;
        /* at this stage dstOPType is ensured to be valid, so no need for error catching default */
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
}

_bool commandOneArguments(AsmInstruction asmInstruction,
        unsigned short commandCode,
        unsigned int supportedAddressing) {

}

_bool commandNulArguments(AsmInstruction asmInstruction,
        unsigned short commandCode,
        unsigned int supportedAddressing) {

}
// #############################################################
// ###### Assembly language implementation #####################
// #############################################################

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
    char *handlerName;

    if(asmLineInstruction->instructionType == INST) {
        handlerName = asmLineInstruction->instruction->INST.command;
    }


    /* Dynamically seek (&find) correct fuction to call
     * We stop either on dynaFuncHandler->function_name == NULL
     * or on match strcmp(pch,  dynaFuncHandler->function_name) == 0
     */
    for(asm_cmd_struct_handler = cmdTable;  asm_cmd_struct_handler->function_name && strcmp(handlerName,  asm_cmd_struct_handler->function_name); asm_cmd_struct_handler++);

    /* If we have found a function at this name */
    if(asm_cmd_struct_handler->function_name) {
        #ifdef DEBUG
            printf("asmCommands.process: function_name = %s\n", asm_cmd_struct_handler->function_name);
        #endif
        /* We want to pass the next location after the function name in the general user input string */
        processCommand(asmLineInstruction, asm_cmd_struct_handler->commandCode, asm_cmd_struct_handler->supportedAddressingBitmap);
    } else {
        handleError(asmLineInstruction->lineNumber, NO_SUCH_ASSEMBLY_COMMAND, handlerName, asmLineInstruction->_log_unparsedAssemblyLine);

    }
}