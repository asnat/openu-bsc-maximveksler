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
    {"Failed to open assembly code file"},
};

void handleError(int lineNumber, int errorCode, char* errorMoreInfo, char* asmCodeLine) {
    fprintf(stderr, "ERRPR #%d: %s\n", errorCode, errorDescriptions[errorCode]);

    if(lineNumber != NULL) { // If we have line number we must surly also have the asmText...
        fprintf(stderr, "\tat %d: %s\n", lineNumber, asmCodeLine);
    }

    if(errorMoreInfo != NULL) {
        fprintf(stderr, "\tAdditional information:\n", errorMoreInfo);
    }
}
