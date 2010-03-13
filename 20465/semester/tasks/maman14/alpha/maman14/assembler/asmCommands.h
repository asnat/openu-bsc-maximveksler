/* 
 * File:   AsmCommands.h
 * Author: hq4ever
 *
 * Created on February 28, 2010, 10:52 PM
 */

#ifndef _ASMCOMMANDS_H
#define	_ASMCOMMANDS_H

#include "constants.h"


void process(AsmInstruction asmLineInstruction);

typedef struct {
    char *function_name;
/*    _bool (*pt2func)(AsmInstruction asmInstruction,
        unsigned short commandCode,
        unsigned int supportedAddressing);
 */
    unsigned short commandCode;
    unsigned int supportedAddressingBitmap;
    /* char *helpText; */
} asm_cmd_struct ;

#endif	/* _ASMCOMMANDS_H */

