/* 
 * File:   ErrorHandler.h
 * Author: hq4ever
 *
 * Created on February 28, 2010, 10:55 PM
 */

#ifndef _ERRORHANDLER_H
#define	_ERRORHANDLER_H

#define SUCCESS 0
#define FAILURE_TO_OPEN_FILE 1
#define NO_SUCH_ASSEMBLY_COMMAND 2
#define WRONG_NUMBER_OF_PARAMETER 3
#define CANT_ALLOCATE_SPACE 4
#define WRONG_ADDRESSING_TYPE 5
#define NO_SUCH_LABEL 6
#define MEMORY_ALLOCATION_FAILURE 7
#define LABEL_ALREADY_EXIST 8
#define FILENAME_TOO_LONG 9
#define ASSEMBLY_LINE_TOO_LONG 10
#define NOT_ENOUGH_ARGUMENTS 11
#define INVALID_DECLARATION_FORMAT 12
#define MISSING_DECLARATION_DATA 13
#define ILEGAL_CHARACTER_IN_COMMAND 14
#define INVALID_ASSEMBLY_SYNTAX 15
#define OPERAND_IS_NOT_VALID_NUMBER 16
#define INVALID_INDIRECT_NOTATION 17
#define INVALID_REGISTER_NOTATION 18
#define INVALID_DIRECT_NOTATION 19

/* Initialize error handler, should be called for each processed line */
void initErrorHandler();

/* Set error number if occured, to be polled by external code */
void setErrorCode(unsigned);

/* Get error number if occured, to be polled by external code */
unsigned int getErrorCode();

/* Logical error has occured and is being reported, we continue after notifiying user about the error */
void handleError(const int unsigned errorCode, const char* errorMoreInfo);

/* Fatal error has occured, we will be quiting the program on this failure. */
void fatalError(const int unsigned errorCode, const char* errorMoreInfo);

/* Set current working assembly line number */
void setLineNumber(const unsigned lineNumber);

/* Get current working assembly line number */
unsigned getLineNumber();

/* Store the unparsed assembly line for logging purposes */
void setUnparsedAssemblyLine(const char* unparsedAssemblyLine);

/* Get the unparsed assembly line for logging purposes */
const char* getUnparsedAssemblyLine();

void setFileName(const char* fileName);

const char* getFileName();

#endif	/* _ERRORHANDLER_H */

