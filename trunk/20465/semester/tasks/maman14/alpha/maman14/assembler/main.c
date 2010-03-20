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

int main(int argc, char **argv) {
    char fileName[FILE_NAME_MAX_SIZE];
    
    int fileNameIndex;
    char* inputArgv;
    
    FILE *fp = NULL;

    /* We are not interested in program name */
    argc--;
    argv++;
    
    while(argc--) { /* For each input argument which represents assembly file names... */
        fileNameIndex = 0;
        inputArgv = *argv;
        
        while(fileNameIndex < FILE_NAME_MAX_SIZE && (fileName[fileNameIndex++] = *inputArgv++));

        /* To the next argv */
        argv++;

        /* Handle error is file name is too long */
        if(fileNameIndex > FILE_NAME_MAX_SIZE - 3) {
            handleError(FILENAME_TOO_LONG, *argv);
            continue; /* Continue to next file */
        }

        /* Add the suffix .as */
        fileName[fileNameIndex-1] = '.'; /* fileNameIndex-1 because we want to override the \0 */
        fileName[fileNameIndex] = 'a';
        fileName[fileNameIndex+1] = 's';
        fileName[fileNameIndex+2] = '\0';

        fp = fopen (fileName, "rt");  /* open the file for reading */
        if(fp == NULL) {
            perror(fileName);
            continue;
        }

        setFileName(fileName);
        
        assemble(fp); /* Calling the assembly engine */

        fclose(fp); /* Close the file reference */
        
    }


    /* FILE *fp; */
    /* printf("%s", FAILURE_TO_OPEN_FILE); */

    return (EXIT_SUCCESS);
}

