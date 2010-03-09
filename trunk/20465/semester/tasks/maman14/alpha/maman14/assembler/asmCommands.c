#include <stdio.h>

#include "asmInstruction.h"
#include "codeSegmentMgr.h"
#include "errorHandler.h"
#include "asmCommands.h"

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

short int commandTwoArguments(AsmInstruction asmInstruction,
        unsigned short commandCode,
        unsigned int supportedAddressing) {

}

short int commandOneArguments(AsmInstruction asmInstruction,
        unsigned short commandCode,
        unsigned int supportedAddressing) {

}

short int commandNulArguments(AsmInstruction asmInstruction,
        unsigned short commandCode,
        unsigned int supportedAddressing) {
    
}
// #############################################################
// ###### Assembly language implementation #####################
// #############################################################

static asm_cmd_struct cmdTable[] = {
    {"mov", commandTwoArguments, 0, 0},
    {"cmp", commandTwoArguments, 1, 0},
    {"add", commandTwoArguments, 2, 0},
    {"sub", commandTwoArguments, 3, 0},
    {"mul", commandTwoArguments, 4, 0},
    {"div", commandTwoArguments, 5, 0},
    {"lea", commandTwoArguments, 6, 0},
    {"inc", commandOneArguments, 7, 0},
    {"dec", commandOneArguments, 8, 0},
    {"jmp", commandOneArguments, 9, 0},
    {"bne", commandOneArguments, 10, 0},
    {"red", commandOneArguments, 11, 0},
    {"prn", commandOneArguments, 12, 0},
    {"jsr", commandOneArguments, 13, 0},
    {"rts", commandNulArguments, 14, 0},
    {"hlt", commandNulArguments, 15, 0},
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
        /* We want to pass the next location after the function name in the general user input string */
        dynaFuncHandler->pt2func(asmLineInstruction, dynaFuncHandler->commandCode, dynaFuncHandler->supportedAddressingBitmap);
    } else {
        handleError(asmLineInstruction->lineNumber, NO_SUCH_ASSEMBLY_COMMAND, handlerName, asmLineInstruction->_log_unparsedAssemblyLine);

    }
}

