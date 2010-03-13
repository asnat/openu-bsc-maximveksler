/* 
 * File:   LineParser.c
 * Author: hq4ever
 *
 * Created on February 27, 2010, 7:00 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "asmInstruction.h"
#include "lineParser.h"
#include "errorHandler.h"
#include "stringUtil.h"

/*
 * 
 */
AsmInstruction parseLine(const char* line) {
    /* bla bla bla */
    line = line;
    /* in the end will returned parsed line. */
    return 0;
}

/* TOOD: This is public only for testing, after all is working this should
    become static and only be called from parseLine */
AsmInstruction allocAsmInstructionINST(
        const char* line,
        const unsigned int lineNumber,
        const unsigned int labelFrom, const unsigned int labelTo,
        const unsigned int cmdFrom, const unsigned int cmdTo,
        const unsigned int srcOPFrom, const unsigned int srcOPTo,
        const AddressingType srcOPType,
        const unsigned int dstOPFrom, const unsigned int dstOPTo,
        const AddressingType dstOPType
        ) {

    AsmInstruction asmInstruction = (AsmInstruction) malloc(sizeof(struct AsmInstruction));
    if(asmInstruction == NULL) {
        fatalError(lineNumber, MEMORY_ALLOCATION_FAILURE, "Can't allocate memory for AsmInstruction", line);
    }

    asmInstruction->lineNumber = lineNumber;
    asmInstruction->_log_unparsedAssemblyLine = line; /* This is OK to do
                                                       because line won't be
                                                       released before our
                                                       logic finishs. */


    asmInstruction->instruction = malloc(sizeof(union InstructionUnion));
    if(asmInstruction->instruction == NULL) {
        fatalError(lineNumber, MEMORY_ALLOCATION_FAILURE, "Can't allocate memory for InstructionUnion", line);
    }

    asmInstruction->instructionType = INST;

    /* String operations */
    asmInstruction->label = substr(line, lineNumber, labelFrom, labelTo);
    asmInstruction->instruction->INST.command = substr(line, lineNumber, cmdFrom, cmdTo);
    asmInstruction->instruction->INST.srcOP = substr(line, lineNumber, srcOPFrom, srcOPTo);
    asmInstruction->instruction->INST.dstOP = substr(line, lineNumber, dstOPFrom, dstOPTo);

    /* Command addressing types */
    asmInstruction->instruction->INST.srcOPType = srcOPType;
    asmInstruction->instruction->INST.dstOPType = dstOPType;

    return asmInstruction;
}

void freeAsmInstruction(AsmInstruction asmInst) {
    /*
     * TODO: Free the whole asmInst memory model...
     * this means go into each and every sub struct, sub union,
     * see what was allocated on the heap and kick it from the
     * memory table, otherwise you have memory leaks, which has
     * direct corelation to the final grade.
     */
    asmInst = asmInst;
}