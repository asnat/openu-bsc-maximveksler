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
        
        if(fgetc(fp) == '\r' || fgetc(fp) == '\n') {
            /* Good, we've found a valid line */
            
        }
        
        if(lineIndex >= LINE_LENGTH-1) {
            handleError(ASSEMBLY_LINE_TOO_LONG, line);

            /* Consume until EOL */
            while(fgetc(fp) != EOF && (fgetc(fp) == '\r' || fgetc(fp) == '\n'));
        }

        line[lineIndex++] = (char) c;
    }


    /* for each line in lines: */
    /* phase1()... */

    processAssemblyLine(line);

    /* for each line in lines: */
    /* phase2()... */

}