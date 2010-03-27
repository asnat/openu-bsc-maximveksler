#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "phaseOne.h"
#include "phaseTwo.h"
#include "errorHandler.h"

#define LINE_LENGTH 81 /* 81 because we have 80 valid chars +1 for \0 */

/*
 * Wrapper function for phase1 & phase2.
 * 
 * Processes assembly lines contained in *fp and produces .o, .ent, .ext files
 * as neccesary.
 *
 * @param fp valid, opened for read file descriptor which points to source file
 * that contains assembly lines.
 */
void assemble(FILE *fp) {
    unsigned int assemblyLineCounter = 1;
    
    /* read lines from fp */
    char line[LINE_LENGTH];
    int lineIndex = 0;

    int c;

    /* Stop for the line */
    line[LINE_LENGTH] = '\0';

    /* Set static pointer to the line array which will be holding
     * the current line */
    setUnparsedAssemblyLine(line);

    while((c = fgetc(fp)) != EOF) {
        setLineNumber(assemblyLineCounter);

        if(lineIndex >= LINE_LENGTH-1) {
            line[lineIndex] = '\0';
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






/* PHASE TWO
 */


     lineIndex = 0;

    

    /* Stop for the line */
    line[LINE_LENGTH] = '\0';

    /* Set static pointer to the line array which will be holding
     * the current line */
    setUnparsedAssemblyLine(line);

    while((c = fgetc(fp)) != EOF) {
        setLineNumber(assemblyLineCounter);

        if(lineIndex >= LINE_LENGTH-1) {
            line[lineIndex] = '\0';
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

/*            phase2processAssemlby(line);*/

            lineIndex = 0;
            assemblyLineCounter++;
        } else {
            line[lineIndex++] = (char) c;
        }
    }

    /* catch last line, which might not be terminated by a \n */
    if(lineIndex > 0) {
        line[lineIndex] = '\0';
       /* phase2processAssemlby(line);*/
    }

}