/* 
 * File:   ErrorHandler.c
 * Author: hq4ever
 *
 * Created on February 28, 2010, 10:53 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "ErrorMessages.h"

static char* errorDescriptions[] = {
    {"SUCCESS"},
    {"Failed to open assembly code file "}, // Error #1 FAILURE_TO_OPEN_FILE
    {"No such assembly command "}, // Error #1 NO_SUCH_ASSEMBLY_COMMAND
};

void handleError(int lineNumber, int errorCode, char* errorMoreInfo, char* asmCodeLine) {
    fprintf(stderr, "ERRPR #%d: %s\n", errorCode, errorDescriptions[errorCode]);

    if(lineNumber != NULL) { // If we have line number we must surly also have the asmText...
        fprintf(stderr, "\tat %d: %s %s\n", lineNumber, asmCodeLine, errorMoreInfo);
    } else if(errorMoreInfo != NULL) {
        fprintf(stderr, "\tAdditional information:\n", errorMoreInfo);
    }
}
