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

int main(int argc, char** argv) {

    //FILE *fp;
    
    //printf("%s", FAILURE_TO_OPEN_FILE);
    AsmInstruction inst = malloc(sizeof(struct AsmInstruction));
    inst->instructionType = INST;
    inst->instruction = malloc(sizeof(union InstructionUnion));

    inst->instruction->INST.command = "mov";
    
    printf("%s\n", inst->instruction->INST.command);
    
    return (EXIT_SUCCESS);
}

