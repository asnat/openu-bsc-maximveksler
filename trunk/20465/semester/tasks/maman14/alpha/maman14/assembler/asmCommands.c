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

short int twoArgumentCommand()
// #############################################################
// ###### Assembly language implementation #####################
// #############################################################
/*void mov(AsmInstruction asmInst) {
    short instructionCode = 0;
    // verify has 2 operands.
    // verify addressing methods are valid.

    //storeToCodeSegment();
}

void cmp(AsmInstruction asmInst) {
    short instructionCode = 1;
}

void add(AsmInstruction asmInst) {
    short instructionCode = 2;
}

void sub(AsmInstruction asmInst) {
    short instructionCode = 3;
}

void mul(AsmInstruction asmInst) {
    short instructionCode = 4;
}

void div(AsmInstruction asmInst) {
    short instructionCode = 5;
}

void lea(AsmInstruction asmInst) {
    short instructionCode = 6;
}

void inc(AsmInstruction asmInst) {
    short instructionCode = 7;
}

void dec(AsmInstruction asmInst) {
    short instructionCode = 8;
}

void jmp(AsmInstruction asmInst) {
    short instructionCode = 9;
}

void bne(AsmInstruction asmInst) {
    short instructionCode = 10;
}

void red(AsmInstruction asmInst) {
    short instructionCode = 11;
}

void prn(AsmInstruction asmInst) {
    short instructionCode = 12;
}

void jsr(AsmInstruction asmInst) {
    short instructionCode = 13;
}

void rts(AsmInstruction asmInst) {
    short instructionCode = 14;
}

void hlt(AsmInstruction asmInst) {
    short instructionCode = 15;
}*/




static conv_t cmdTable[] = {
    {"mov", twoParm},
    {"cmp", twoParm},
    {"add", twoParm},
    {"sub", twoParm},
    {"mul", twoParm},
    {"div", twoParm},
    {"lea", twoParm},
    {"inc", oneParm},
    {"dec", oneParm},
    {"jmp", oneParm},
    {"bne", oneParm},
    {"red", oneParm},
    {"prn", oneParm},
    {"jsr", oneParm},
    {"rts", noParm},
    {"hlt", noParm},
    {NULL, NULL}
};

void process(AsmInstruction asmLineInstruction) {
    conv_t *dynaFuncHandler;
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
        dynaFuncHandler->pt2func(asmLineInstruction);
    } else {
        handleError(asmLineInstruction->lineNumber, NO_SUCH_ASSEMBLY_COMMAND, handlerName, asmLineInstruction->_log_unparsedAssemblyLine);

    }
}

