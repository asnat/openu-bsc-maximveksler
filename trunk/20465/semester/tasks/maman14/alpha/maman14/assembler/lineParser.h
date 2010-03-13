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

/*
 * Gets input line which is assembly code line and builds AsmInstruction struct from it.
 * strings that go into each field should be pre calculated.
 */
AsmInstruction allocAsmInstructionINST(
        const char* line,
        const unsigned int lineNumber,
        const unsigned int labelFrom, const unsigned int labelTo,
        const unsigned int cmdFrom, const unsigned int cmdTo,
        const unsigned int srcOPFrom, const unsigned int srcOPTo,
        const AddressingType srcOPType,
        const unsigned int dstOPFrom, const unsigned int dstOPTo,
        const AddressingType dstOPType
        );

void freeAsmInstruction(AsmInstruction asmInst);

#endif	/* _LINEPARSER_H */

