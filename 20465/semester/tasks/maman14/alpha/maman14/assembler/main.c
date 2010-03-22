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
#include "errorHandler.h"
#include "assembler.h"

#define FILE_NAME_MAX_SIZE 512
#define SUFFIX_SIZE 3
#define ASM_FILE_SUFFIX ".as"

    int maxTest = 1;
    int doronTest = 2;

void doMaxTest() {
    AsmInstruction inst = allocAsmInstructionINST(
            "mov LENGTH, r1",
            0, 0, /* label */
            0, 3, /* cmd */
            4, 10, /* srcOPFrom */
            12, 14 /* srcOPFrom */
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
    /*
    char name[] = "doron";
    unsigned address = 100;
    _bool rc;


    initLabelTable();
    rc = addLabel(name, address);
    address = 200;
    rc = getLabelAddress(name,&address);
    printf("%hu %u\n",rc,address);
    */
}

int main(int argc,char** argv){
    char* currentFilePath; /* the current proccess file path including the suffix .as*/
    FILE *currentFileHandle; /* the current proccess file handle */
    int fileNameSize; /* the size of the file name*/
    int currentArg; /* point to the current argument */

    /* see if any atrgument given */
    if (argc == 1)
        fatalError(NOT_ENOUGH_ARGUMENTS, "no file to process");

    for(currentArg=1;currentArg < argc;currentArg++){
        fileNameSize = (int) strlen(argv[currentArg])+1;
        
        if ( fileNameSize > FILE_NAME_MAX_SIZE - SUFFIX_SIZE) {
           handleError(FILENAME_TOO_LONG, argv[currentArg]);
        }
        else {

            if ((currentFilePath = (char*) malloc(fileNameSize*sizeof(char)+SUFFIX_SIZE)) == NULL)
                fatalError(MEMORY_ALLOCATION_FAILURE, argv[currentArg]);

            strcpy(currentFilePath,argv[currentArg]);
            strcat(currentFilePath,ASM_FILE_SUFFIX);
            if ((currentFileHandle = fopen(currentFilePath, "r")) == NULL)
                perror(currentFilePath);
            else {
                setFileName(currentFilePath);
                assemble(currentFileHandle);
                fclose(currentFileHandle);
            }
            free(currentFilePath);
         }
    }
    return EXIT_SUCCESS;
}

