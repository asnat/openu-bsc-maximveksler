/* 
 * File:   main.c
 * Author: hq4ever
 *
 * Created on February 25, 2010, 9:36 PM
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "asmInstruction.h"
#include "asmCommands.h"
#include "lineParser.h"
#include "label.h"
#include "errorHandler.h"
#include "assembler.h"
#include "errorHandler.h"
#include "outputFilesHandler.h"

#define FILE_NAME_MAX_SIZE 512
#define SUFFIX_SIZE 3
#define ASM_FILE_SUFFIX ".as"

int main(int argc, char** argv) {
    char* currentFilePath; /* the current proccess file path including the suffix .as*/
    int fileNameSize; /* the size of the file name*/
    int currentArg; /* point to the current argument */

    /* see if any argument given */
    if (argc == 1)
        fatalError(NOT_ENOUGH_ARGUMENTS, "no file to process");

    for(currentArg=1; currentArg < argc; currentArg++) {
        fileNameSize = (int) strlen(argv[currentArg])+1;

        /* check if file name is to long */
        if (fileNameSize > FILE_NAME_MAX_SIZE - SUFFIX_SIZE) {
            handleError(FILENAME_TOO_LONG, argv[currentArg]);
        } else {

            /* find the name o f the source file include the suffix */
            if ((currentFilePath = (char*) malloc(fileNameSize*sizeof(char)+SUFFIX_SIZE)) == NULL)
                fatalError(MEMORY_ALLOCATION_FAILURE, argv[currentArg]);
            
            strcpy(currentFilePath, argv[currentArg]);
            strcat(currentFilePath, ASM_FILE_SUFFIX);

            setFileName(currentFilePath); /* set file name  for error handling */
            initOutputFiles(argv[currentArg]); /* set output files path names */

            assemble(currentFilePath); /* process the source file */

            freeOutputFiles(); /* Free phase 2 output file name strings */
            
            free(currentFilePath);
         }
    }
    
    return EXIT_SUCCESS;
}

