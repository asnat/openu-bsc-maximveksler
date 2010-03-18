/* 
 * File:   main.c
 * Author: hq4ever
 *
 * Created on February 25, 2010, 9:36 PM
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "errorHandler.h"

#include "asmInstruction.h"
#include "asmCommands.h"
#include "lineParser.h"
#include "label.h"

    int maxTest = 1;
    int doronTest = 2;

void doMaxTest() {
    AsmInstruction inst = allocAsmInstructionINST(
            "mov LENGTH, r1",
            17,
            0, 0, /* label */
            0, 3, /* cmd */
            4, 10, /* srcOPFrom */
            DIRECT,
            12, 14, /* srcOPFrom */
            REGISTER
            );

/*
    malloc(sizeof(struct AsmInstruction));
    inst->instructionType = INST;

    inst->instruction = malloc(sizeof(union InstructionUnion));
    inst->instruction->INST.command = malloc(3);
    "mov";
    inst->instruction->INST.srcOP = "LENGTH";
    inst->instruction->INST.srcOPType = DIRECT;
    inst->instruction->INST.dstOP = "r1";
    inst->instruction->INST.dstOPType = REGISTER;

    inst->_log_unparsedAssemblyLine = "mov LENGTH, r1";
    inst->lineNumber = 1;
*/
    
    process(inst);
}

void doDoronTest() {
    char name[] = "doron";
    unsigned address = 100;
    errorCode rc;
    initLabelTable();
    rc = addLabel(name, address);
    printf("%hu",rc);
}

int main() {
    int thisTest = doronTest;

    if(thisTest == maxTest)
        doMaxTest();
    else
        doDoronTest();

    /* FILE *fp; */
    /* printf("%s", FAILURE_TO_OPEN_FILE); */

    return (EXIT_SUCCESS);
}

