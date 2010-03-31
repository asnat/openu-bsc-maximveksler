#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "phaseOne.h"
#include "phaseTwo.h"
#include "errorHandler.h"
#include "outputFilesHandler.h"
#include "label.h"
#include "codeSegmentMgr.h"
#include "dataSegmentMgr.h"
#include "hash.h"

#define MAXIMUM_LINE_LENGTH 1024
#define ASSEMBLER_DEBUG 1

/*
 * Wrapper function for phase1 & phase2.
 * 
 * Processes assembly lines contained in *fp and produces .o, .ent, .ext files
 * as neccesary.
 *
 * @param fp valid, opened for read file descriptor which points to source file
 * that contains assembly lines.
 */
void assemble(char* currentFilePath) {
    FILE *fp;
    unsigned int assemblyLineCounter = 1;
    
    /* read lines from fp */
    char line[MAXIMUM_LINE_LENGTH];
    int lineIndex = 0;
    int c;

    if ((fp = fopen(currentFilePath, "r")) == NULL) {
        perror(currentFilePath);
        return;
    }

    /* Stop for the line */
    line[MAXIMUM_LINE_LENGTH-1] = '\0';

    /* Init holders for each file */
    initErrorHandler();
    initLabelTable();
    initCodeSegmentMgr();
    initDataSegmentMgr();


    /* Set static pointer to the line array which will be holding
     * the current line */
    setUnparsedAssemblyLine(line);

    while((c = fgetc(fp)) != EOF) {
        setLineNumber(assemblyLineCounter);

        if(lineIndex >= MAXIMUM_LINE_LENGTH) {
            line[MAXIMUM_LINE_LENGTH-1] = '\0';
            handleError(ASSEMBLY_LINE_TOO_LONG, NULL);

            /* Consume until new line or until EOL */
            while((c = fgetc(fp)) != EOF) {
                if(c == '\r' || c == '\n') {
                    break; /* reached valid stop character which notifies new line */
                }
            }

            lineIndex = 0;
            assemblyLineCounter++;
        } else if(c == '\r' || c == '\n') {
            /* Good, we've found a valid line */
            line[lineIndex] = '\0';
            
            processAssemblyLine(line);
            
            lineIndex = 0;
            assemblyLineCounter++;
        } else {
            line[lineIndex++] = (char) c;
        }
    }

    /* catch last line, which might not be terminated by a \n */
    if(lineIndex > 0) {
        line[lineIndex] = '\0';
        processAssemblyLine(line);
    }

    /* Close file descripter after phase 1 processing */
    fclose(fp);


/* PHASE TWO
 */

    assemblyLineCounter = 1;
    
    /* open the file for read */
    if ((fp = fopen(currentFilePath, "r")) == NULL) {
        perror(currentFilePath);
        return;
    }

    /* read the file from the begining*/
    fseek(fp,0,SEEK_SET);

    /* reset the line index */
    lineIndex = 0;
    /* reset the code segment index*/
    resetIC();

    /* Stop for the line */
    line[MAXIMUM_LINE_LENGTH-1] = '\0';

    /* Set static pointer to the line array which will be holding
     * the current line */
    setUnparsedAssemblyLine(line);

    while((c = fgetc(fp)) != EOF) {
        setLineNumber(assemblyLineCounter);

        if(lineIndex >= MAXIMUM_LINE_LENGTH) {
            line[MAXIMUM_LINE_LENGTH-1] = '\0';
            handleError(ASSEMBLY_LINE_TOO_LONG, NULL);

           /* Consume until EOL */
           while((c = fgetc(fp)) != EOF) {
                if(c == '\r' || c == '\n') {
                    break;
                }
            }

            lineIndex = 0;
            assemblyLineCounter++;
        } else if(c == '\r' || c == '\n') {
            /* Good, we've found a valid line */
            line[lineIndex] = '\0';

            /* phase 2 processing of the line we found*/
            phase2processAssemlby(line);

            lineIndex = 0;
            assemblyLineCounter++;
        } else {
            line[lineIndex++] = (char) c;
        }
    }

    /* catch last line, which might not be terminated by a \n */
    if(lineIndex > 0) {
        line[lineIndex] = '\0';
        /* phase 2 processing of the last line we found*/
       phase2processAssemlby(line);
    }

    /* print the object file */
    if (c == EOF){
            writeToObjFile();
    }

    /* free the output files pointers of the current file */
    if(getErrorCode() != SUCCESS ) {
        removeOutputFiles();
    }

    /* free the current file label table */
    freeLabelTable();
}
