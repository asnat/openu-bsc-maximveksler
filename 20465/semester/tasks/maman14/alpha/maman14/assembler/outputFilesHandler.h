/* 
 * File:   outpuFilesHandler.h
 * Author: dorons
 *
 * Created on March 22, 2010, 12:28 AM
 */

#ifndef _OUTPUFILESHANDLER_H
#define	_OUTPUFILESHANDLER_H

#ifndef _CONSTANTS_H
#include "constants.h"
#endif

#define OBJ_FILE 0
#define EXT_FILE 1
#define ENT_FILE 2

void initOutputFiles(char*);
_bool writeObjectFileFirstRow();
_bool writeToObjFile(unsigned short, unsigned short, char);
_bool writeToOutputFile(int , char*, unsigned short);


#endif	/* _OUTPUFILESHANDLER_H */

