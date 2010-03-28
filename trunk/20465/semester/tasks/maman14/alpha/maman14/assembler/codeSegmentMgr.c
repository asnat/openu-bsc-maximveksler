/* 
 * File:   CodeSegmentMgr.c
 * Author: hq4ever
 *
 * Created on February 27, 2010, 10:47 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "codeSegmentMgr.h"
#include "asmInstruction.h"

static unsigned IC = 0;

static unsigned short codeSegment[SEGMENT_MAXIMUM_SIZE];
static LinkerAddress codeLinkertype[SEGMENT_MAXIMUM_SIZE];

void resetCode() {
    unsigned int i;
    for(i = 0; i < SEGMENT_MAXIMUM_SIZE; i++) {
        codeSegment[i] = (unsigned int) NULL;
    }
    for(i = 0; i < SEGMENT_MAXIMUM_SIZE; i++) {
        codeLinkertype[i] = UNKNOWN_TYPE;
    }

    resetIC();
}

void resetIC(void){
    IC = 0;
}

unsigned int getIC() {
    return IC;
}

void forward() {
    IC++;
}

unsigned short storeCode(unsigned short data) {
    codeSegment[IC] = data;
    IC += 1;
    
    return codeSegment[IC-1];
}

unsigned short getCode(unsigned short index) {
    return codeSegment[index];
}

LinkerAddress getCodeLinkerType(unsigned short index){
    return codeLinkertype[index];
}

void setCodeLinkerType(LinkerAddress type){
    codeLinkertype[IC] = type;
}