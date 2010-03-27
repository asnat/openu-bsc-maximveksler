/* 
 * File:   CodeSegmentMgr.c
 * Author: hq4ever
 *
 * Created on February 27, 2010, 10:47 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "constants.h"

static unsigned IC = 0;
static unsigned short codeSegment[SEGMENT_MAXIMUM_SIZE];

void resetCode() {
    unsigned int i;
    for(i = 0; i <= IC; i++) {
        codeSegment[i] = (unsigned int) NULL;
    }

    IC = 0;
}

unsigned int getIC() {
    return IC;
}

unsigned short storeCode(unsigned short data) {
    codeSegment[IC] = data;
    IC += 1;
    
    return codeSegment[IC-1];
}

unsigned short* getCode(unsigned index) {
    return codeSegment[index];
}