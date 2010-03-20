#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "phaseOne.h"
#include "errorHandler.h"

#define LINE_LENGTH 81

void assemble(FILE *fp) {
    unsigned int assemblyLineCounter = 1;
    
    /* read lines from fp */
    char line[LINE_LENGTH];
    int lineIndex = 0;

    int c;

    /* Stop for the line */
    line[LINE_LENGTH] = '\0';
    
    while((c = fgetc(fp)) != EOF) {
        setLineNumber(assemblyLineCounter);
        setUnparsedAssemblyLine(line);

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

            continue;
        } else

        if(c == '\r' || c == '\n') {
            /* Good, we've found a valid line */
            line[lineIndex] = '\0';
            
            processAssemblyLine(line);
            
            lineIndex = 0;
            assemblyLineCounter++;

            continue;
        }

        line[lineIndex++] = (char) c;        
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

}