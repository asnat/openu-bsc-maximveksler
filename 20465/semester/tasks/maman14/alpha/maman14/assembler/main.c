/* 
 * File:   main.c
 * Author: hq4ever
 *
 * Created on February 25, 2010, 9:36 PM
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ErrorMessages.h"

#include "AsmInstruction.h"

    int maxTest = 1;
    int doronTest = 2;

int main(int argc, char** argv) {
    int thisTest = maxTest;

    if(thisTest == maxTest)
        doMaxTest();
    else
        doDoronTest();

    //FILE *fp;
    //printf("%s", FAILURE_TO_OPEN_FILE);

    
    return (EXIT_SUCCESS);
}

doMaxTest() {
        AsmInstruction inst = malloc(sizeof(struct AsmInstruction));
    inst->instructionType = INST;

    inst->instruction = malloc(sizeof(union InstructionUnion));
    inst->instruction->INST.command = "mov";
    inst->instruction->INST.operand1 = "LENGTH";
    inst->instruction->INST.operand1Type = DIRECT;
    inst->instruction->INST.operand2 = "r1";
    inst->instruction->INST.operand2Type = REGISTER;
}

doDoronTest() {
    
}