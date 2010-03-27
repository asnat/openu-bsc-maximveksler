/* 
 * File:   label.h
 * Author: doron
 *
 * Created on March 2, 2010, 1:32 PM
 */

#ifndef _LABEL_H
#define	_LABEL_H

#ifndef _CONSTANTS_H
#include "constants.h"
#endif

#ifndef _INSTRUCTIONSTRUCTURE_H
#include "asmInstruction.h"
#endif

void freeLabelTable(void);
void initLabelTable(void);
_bool getLabelAddress(char*, unsigned short*);
_bool addLabel(char* labelName, LinkerAddress type, unsigned short data);
LinkerAddress getLabelType(char* labelName);

#endif	/* _LABEL_H */

