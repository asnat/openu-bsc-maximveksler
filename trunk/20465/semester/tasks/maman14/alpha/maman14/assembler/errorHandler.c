/* 
 * File:   ErrorHandler.c
 * Author: hq4ever
 *
 * Created on February 28, 2010, 10:53 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "errorHandler.h"

static unsigned errorCode;

static const char* errorDescriptions[] = {
    "SUCCESS",
    "Failed to open assembly code file ", /* Error #1 FAILURE_TO_OPEN_FILE */
    "No such assembly command ", /* Error #2 NO_SUCH_ASSEMBLY_COMMAND */
    "Wrong number of parmeter", /* Error #3 WRONG_NUMBER_OF_PARAMETER*/
    "Cant allocate space", /* Error #4 CANT_ALLOCATE_SPACE */
    "Wrong addressing type", /* Error #5 WRONG_ADDRESSING_TYPE */
    "No such labal", /* Error #6 NO_SUCH_LABEL */
    "Failed to allocate memory" /* Error #7 MEMORY_ALLOCATION_FAILURE */
};

void setErrorCode(unsigned errorNum){
    errorCode = errorNum;
}

void handleError(const unsigned lineNumber, const char* errorMoreInfo, const char* asmCodeLine) {
    fprintf(stderr, "ERRPR #%d: %s\n", errorCode, errorDescriptions[errorCode]);

    if(lineNumber != NULL) { /* If we have line number we must surly also have the asmText... */
        fprintf(stderr, "\tat %d: %s => %s\n", lineNumber, asmCodeLine, errorMoreInfo);
    } else if(errorMoreInfo != NULL) {
        fprintf(stderr, "\tAdditional information: %s\n", errorMoreInfo);
    }
}

void fatalError(const unsigned lineNumber, const char* errorMoreInfo, const char* asmCodeLine) {
    handleError(lineNumber, errorCode, errorMoreInfo, asmCodeLine);

    exit(EXIT_FAILURE);
}
