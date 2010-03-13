/* 
 * File:   LineParser.c
 * Author: hq4ever
 *
 * Created on February 27, 2010, 7:00 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "asmInstruction.h"

/*
 * 
 */
AsmInstruction parseLine(char* line) {
    // bla bla bla

    // in the end will returned parsed line.
    return 0;
}

void freeAsmInstruction(AsmInstruction asmInst) {
    /*
     * TODO: Free the whole asmInst memory model...
     * this means go into each and every sub struct, sub union,
     * see what was allocated on the heap and kick it from the
     * memory table, otherwise you have memory leaks, which has
     * direct corelation to the final grade.
     */
}