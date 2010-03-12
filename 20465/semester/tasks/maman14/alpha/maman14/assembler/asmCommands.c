#include <stdio.h>

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


static unsigned short storeToCodeSegment(unsigned short dstRgstrCode,
        unsigned short dstAddrTypeCode,
        unsigned short srcRgstrCode,
        unsigned short srcAddrTypeCode,
        unsigned short instCode) {

    unsigned short instruction = 0;

    instruction = dstRgstrCode;
    instruction &= (dstAddrTypeCode << 3);
    instruction &= (srcRgstrCode << 6);
    instruction &= (srcAddrTypeCode << 9);
    instruction &= (instCode << 12);

    storeData(instruction);
}

_bool commandTwoArguments(AsmInstruction asmInstruction,
        unsigned short commandCode,
        unsigned int supportedAddressing) {

    if(! (OP_SRC_CBIT_EXTRACT(supportedAddressing) & OP_SRC_CBIT(asmInstruction->instruction->INST.srcOPType))) {
        /* Check that the first operand type supplied is valid */
        handleError(asmInstruction->lineNumber, WRONG_ADDRESSING_TYPE, "Source operand is illigal for instruction", asmInstruction->_log_unparsedAssemblyLine);
        return FALSE;
    }

    if(! (OP_DST_CBIT_EXTRACT(supportedAddressing) & OP_DST_CBIT(asmInstruction->instruction->INST.srcOPType))) {
        handleError(asmInstruction->lineNumber, WRONG_ADDRESSING_TYPE, "Destination operand is illigal for instruction", asmInstruction->_log_unparsedAssemblyLine);
        return FALSE;
    }

    /* Reaching here we know that our supplied operand for instruction are indeed valid. YAY! */


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
    {"mov", commandTwoArguments, 0,
            OP_SRC_CBIT(IMMIDIATE) | OP_SRC_CBIT(DIRECT) | OP_SRC_CBIT(INDIRECT) | OP_SRC_CBIT(REGISTER)
            | OP_DST_CBIT(DIRECT) | OP_DST_CBIT(INDIRECT) | OP_DST_CBIT(REGISTER)
    },
    {"cmp", commandTwoArguments, 1,
            OP_SRC_CBIT(IMMIDIATE) | OP_SRC_CBIT(DIRECT) | OP_SRC_CBIT(INDIRECT) | OP_SRC_CBIT(REGISTER)
            | OP_DST_CBIT(IMMIDIATE) | OP_DST_CBIT(DIRECT) | OP_DST_CBIT(INDIRECT) | OP_DST_CBIT(REGISTER)
    },
    {"add", commandTwoArguments, 2,
            OP_SRC_CBIT(IMMIDIATE) | OP_SRC_CBIT(DIRECT) | OP_SRC_CBIT(INDIRECT) | OP_SRC_CBIT(REGISTER)
            | OP_DST_CBIT(DIRECT) | OP_DST_CBIT(INDIRECT) | OP_DST_CBIT(REGISTER)
    },
    {"sub", commandTwoArguments, 3,
            OP_SRC_CBIT(IMMIDIATE) | OP_SRC_CBIT(DIRECT) | OP_SRC_CBIT(INDIRECT) | OP_SRC_CBIT(REGISTER)
            | OP_DST_CBIT(DIRECT) | OP_DST_CBIT(INDIRECT) | OP_DST_CBIT(REGISTER)
    },
    {"mul", commandTwoArguments, 4,
            OP_SRC_CBIT(IMMIDIATE) | OP_SRC_CBIT(DIRECT) | OP_SRC_CBIT(INDIRECT) | OP_SRC_CBIT(REGISTER)
            | OP_DST_CBIT(DIRECT) | OP_DST_CBIT(INDIRECT) | OP_DST_CBIT(REGISTER)
    },
    {"div", commandTwoArguments, 5,
            OP_SRC_CBIT(IMMIDIATE) | OP_SRC_CBIT(DIRECT) | OP_SRC_CBIT(INDIRECT) | OP_SRC_CBIT(REGISTER)
            | OP_DST_CBIT(DIRECT) | OP_DST_CBIT(INDIRECT) | OP_DST_CBIT(REGISTER)
    },
    {"lea", commandTwoArguments, 6,
            OP_SRC_CBIT(DIRECT)
            | OP_DST_CBIT(DIRECT) | OP_DST_CBIT(INDIRECT) | OP_DST_CBIT(REGISTER)
    },
    {"inc", commandOneArguments, 7,
            OP_SRC_CBIT(NO_OP)
            | OP_DST_CBIT(DIRECT) | OP_DST_CBIT(INDIRECT) | OP_DST_CBIT(REGISTER)
    },
    {"dec", commandOneArguments, 8,
            OP_SRC_CBIT(NO_OP)
            | OP_DST_CBIT(DIRECT) | OP_DST_CBIT(INDIRECT) | OP_DST_CBIT(REGISTER)
    },
    {"jmp", commandOneArguments, 9,
            OP_SRC_CBIT(NO_OP)
            | OP_DST_CBIT(DIRECT) | OP_DST_CBIT(INDIRECT)
    },
    {"bne", commandOneArguments, 10,
            OP_SRC_CBIT(NO_OP)
            | OP_DST_CBIT(DIRECT) | OP_DST_CBIT(INDIRECT)
    },
    {"red", commandOneArguments, 11,
            OP_SRC_CBIT(NO_OP)
            | OP_DST_CBIT(DIRECT) | OP_DST_CBIT(INDIRECT) | OP_DST_CBIT(REGISTER)
    },
    {"prn", commandOneArguments, 12,
            OP_SRC_CBIT(NO_OP)
            | OP_DST_CBIT(IMMIDIATE) | OP_DST_CBIT(DIRECT) | OP_DST_CBIT(INDIRECT) | OP_DST_CBIT(REGISTER)
    },
    {"jsr", commandOneArguments, 13,
            OP_SRC_CBIT(NO_OP)
            | OP_DST_CBIT(DIRECT) | OP_DST_CBIT(INDIRECT)
    },
    {"rts", commandNulArguments, 14,
            OP_SRC_CBIT(NO_OP)
            | OP_DST_CBIT(NO_OP)
    },
    {"hlt", commandNulArguments, 15,
            OP_SRC_CBIT(NO_OP)
            | OP_DST_CBIT(NO_OP)
    },
    {NULL, NULL, (int)NULL}
};

void process(AsmInstruction asmLineInstruction) {
    asm_cmd_struct *dynaFuncHandler;
    char *handlerName;

    if(asmLineInstruction->instructionType == INST) {
        handlerName = asmLineInstruction->instruction->INST.command;
    }


    /* Dynamically seek (&find) correct fuction to call
     * We stop either on dynaFuncHandler->function_name == NULL
     * or on match strcmp(pch,  dynaFuncHandler->function_name) == 0
     */
    for(dynaFuncHandler = cmdTable;  dynaFuncHandler->function_name && strcmp(handlerName,  dynaFuncHandler->function_name); dynaFuncHandler++);

    /* If we have found a function at this name */
    if(dynaFuncHandler->function_name) {
        #ifdef DEBUG
            printf("asmCommands.process: function_name = %s\n", dynaFuncHandler->function_name);
        #endif
        /* We want to pass the next location after the function name in the general user input string */
        dynaFuncHandler->pt2func(asmLineInstruction, dynaFuncHandler->commandCode, dynaFuncHandler->supportedAddressingBitmap);
    } else {
        handleError(asmLineInstruction->lineNumber, NO_SUCH_ASSEMBLY_COMMAND, handlerName, asmLineInstruction->_log_unparsedAssemblyLine);

    }
}

