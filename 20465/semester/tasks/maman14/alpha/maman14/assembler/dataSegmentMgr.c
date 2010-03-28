/*
 * File:   CodeSegmentMgr.c
 * Author: hq4ever
 *
 * Created on February 27, 2010, 10:47 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "constants.h"

static unsigned DC = 0;
static unsigned short dataSegment[SEGMENT_MAXIMUM_SIZE];

void resetData() {
    unsigned int i;
    for(i = 0; i < SEGMENT_MAXIMUM_SIZE; i++) {
        dataSegment[i] = (unsigned int) NULL;
    }

    DC = 0;
}

void forwardDC(){
    DC++;
}

void resetDC(){
    DC = 0;
}
unsigned int getDC() {
    return DC;
}

unsigned short storeData(unsigned short data) {
    dataSegment[DC] = data;
    DC += 1;

    return dataSegment[DC-1];
}

unsigned short* getData() {
    return dataSegment;
}