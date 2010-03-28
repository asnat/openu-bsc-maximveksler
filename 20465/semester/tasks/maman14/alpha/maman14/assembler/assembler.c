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
    unsigned short codeSegmentAmount, dataSegmentAmount;

    if ((fp = fopen(currentFilePath, "r")) == NULL) {
        
    }

    /* Stop for the line */
    line[MAXIMUM_LINE_LENGTH] = '\0';

    initLabelTable();
    resetCode();

    /* Set static pointer to the line array which will be holding
     * the current line */
    setUnparsedAssemblyLine(line);

    while((c = fgetc(fp)) != EOF) {
        setLineNumber(assemblyLineCounter);

        if(lineIndex >= MAXIMUM_LINE_LENGTH) {
            line[lineIndex] = '\0';
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
    
    /* for each line in lines: */
    /* phase1()... */

    /* for each line in lines: */
    /* phase2()... */


    fclose(fp);
    
    printf("Kicking off phase 2 !!!\n");
    


/* PHASE TWO
 */
    if ((fp = fopen(currentFilePath, "r")) == NULL) {

    }

    fseek(fp,0,SEEK_SET);
    lineIndex = 0;
    codeSegmentAmount = getIC() - (unsigned short)1;
    dataSegmentAmount = getDC() - (unsigned short)1;
    writeObjectFileFirstRow();
    resetIC();

    /* Stop for the line */
    line[MAXIMUM_LINE_LENGTH] = '\0';

    /* Set static pointer to the line array which will be holding
     * the current line */
    setUnparsedAssemblyLine(line);

    while((c = fgetc(fp)) != EOF) {
        setLineNumber(assemblyLineCounter);

        if(lineIndex >= MAXIMUM_LINE_LENGTH-1) {
            line[lineIndex] = '\0';
            handleError(TEXT_INPUT_OVERFLOW, NULL);

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
       phase2processAssemlby(line);
    }
    if (c == EOF ){
            writeToObjFile(codeSegmentAmount, dataSegmentAmount);
    }
}
