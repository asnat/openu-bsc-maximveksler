/* 
 * File:   ErrorHandler.c
 * Author: hq4ever
 *
 * Created on February 28, 2010, 10:53 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "errorHandler.h"

static unsigned int _errorCode;
static unsigned _lineNumber;
static const char* _unparsedAssemblyLine;
static const char* _fileName;

static const char* errorDescriptions[] = {
    "SUCCESS",
    "Failed to open assembly code file ", /* Error #1 FAILURE_TO_OPEN_FILE */
    "No such assembly command ", /* Error #2 NO_SUCH_ASSEMBLY_COMMAND */
    "Wrong number of parmeter", /* Error #3 WRONG_NUMBER_OF_PARAMETER*/
    "Cant allocate space", /* Error #4 CANT_ALLOCATE_SPACE */
    "Wrong addressing type", /* Error #5 WRONG_ADDRESSING_TYPE */
    "No such labal", /* Error #6 NO_SUCH_LABEL */
    "Failed to allocate memory", /* Error #7 MEMORY_ALLOCATION_FAILURE */
    "Label redefined", /* Error #8 LABEL_ALREADY_EXIST */
    "File name is too long", /* Error #9 FILENAME_TOO_LONG */
    "Assembly line is too long", /* Error #10 ASSEMBLY_LINE_TOO_LONG */
    "At least 1 assembly file should be supplied", /* #11 NOT_ENOUGH_ARGUMENTS */
    "Invalid declaration format", /* #12 INVALID_DECLARATION_FORMAT */
    "Missing declaration data", /* 13 MISSING_DECLARATION_DATA */
    "Iligal character in command", /* 14 ILEGAL_CHARACTER_IN_COMMAND */
    "Invalid assembly syntax", /* 15 INVALID_ASSEMBLY_SYNTAX */
    "Operand not valid number", /* 16 OPERAND_IS_NOT_VALID_NUMBER */
    "Invalid indirect notation", /* 17 INVALID_INDIRECT_NOTATION */
    "Invalid register notation", /* 18 INVALID_REGISTER_NOTATION */
    "Invalid direct notation", /* 19 INVALID_DIRECT_NOTATION */
    "Failed adding label for phase two processing", /* 20 LABEL_ADDING_FAILURE */
    "Data declaration is empty" /* 21 DATA_DECLARATION_EMPTY */
    "String declaration is empty" /* 22 STRING_DECLARATION_EMPTY */
};

void initErrorHandler() {
    _errorCode = SUCCESS;
    _lineNumber = 0;
    _unparsedAssemblyLine = NULL;
}

void setUnparsedAssemblyLine(const char* unparsedAssemblyLine) {
    _unparsedAssemblyLine = unparsedAssemblyLine;
}

const char* getUnparsedAssemblyLine() {
    return _unparsedAssemblyLine;
}

void setErrorCode(unsigned errorCode) {
    _errorCode = errorCode;
}

unsigned int getErrorCode() {
    return _errorCode;
}

void setLineNumber(const unsigned lineNumber) {
    _lineNumber = lineNumber;
}

unsigned getLineNumber() {
    return _lineNumber;
}

void setFileName(const char* fileName) {
    _fileName = fileName;
}

const char* getFileName() {
    return _fileName;
}

void handleError(const int unsigned errorCode, const char* errorMoreInfo) {
    setErrorCode(errorCode);
    
    fprintf(stderr, "ERROR #%d: %s\n", _errorCode, errorDescriptions[_errorCode]);

    if(_lineNumber != (const unsigned) NULL) { /* If we have line number we must surly also have the asmText... */
        fprintf(stderr, "\t%s at %d: %s\n", _fileName, _lineNumber, _unparsedAssemblyLine);
        if(errorMoreInfo != NULL) {
            fprintf(stderr, "\tMore Info: %s\n", errorMoreInfo);
        }
    } else if(errorMoreInfo != NULL) {
        fprintf(stderr, "\tAdditional information: %s\n", errorMoreInfo);
    }
}

void fatalError(const int unsigned errorCode, const char* errorMoreInfo) {
    handleError(errorCode, errorMoreInfo);

    exit(EXIT_FAILURE);
}
