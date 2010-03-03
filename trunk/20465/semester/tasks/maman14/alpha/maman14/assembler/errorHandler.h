/* 
 * File:   ErrorHandler.h
 * Author: hq4ever
 *
 * Created on February 28, 2010, 10:55 PM
 */

#ifndef _ERRORHANDLER_H
#define	_ERRORHANDLER_H

#define FAILURE_TO_OPEN_FILE 1
#define NO_SUCH_ASSEMBLY_COMMAND 2
#define WRONG_NUMBER_OF_PARAMETER 3
#define CANT_ALLOCATE_SPACE 4
#define WRONG_ADDRESSING_TYPE 5
#define NO_SUCH_LABEL 6#define FAILURE_TO_OPEN_FILE 1
#define NO_SUCH_ASSEMBLY_COMMAND 2
#define WRONG_NUMBER_OF_PARAMETER 3
#define CANT_ALLOCATE_SPACE 4
#define WRONG_ADDRESSING_TYPE 5
#define NO_SUCH_LABEL 6

void handleError(int lineNumber, int errorCode, char* errorMoreInfo, char* asmCodeLine);

#endif	/* _ERRORHANDLER_H */

