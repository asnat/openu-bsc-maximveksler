/* 
 * File:   LineParser.h
 * Author: hq4ever
 *
 * Created on February 27, 2010, 7:04 PM
 */

#include "asmInstruction.h"

#ifndef _LINEPARSER_H
#define	_LINEPARSER_H

AsmInstruction parseLine(const char* line);


void freeAsmInstruction(AsmInstruction asmInst);

#endif	/* _LINEPARSER_H */

