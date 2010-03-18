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
#define LABEL_ALREADY_EXIST 7
#define MEMORY_ALLOCATION_FAILURE 8

typedef unsigned short errorCode;

/* Logical error has occured and is being reported, we continue after notifiying user about the error */
void handleError(const int unsigned lineNumber, const int unsigned errorCode, const char* errorMoreInfo, const char* asmCodeLine);

/* Fatal error has occured, we will be quiting the program on this failure. */
void fatalError(const int unsigned lineNumber, const int unsigned errorCode, const char* errorMoreInfo, const char* asmCodeLine);


#endif	/* _ERRORHANDLER_H */

