/*
 * File:   CodeSegmentMgr.c
 * Author: hq4ever
 *
 * Created on February 27, 2010, 10:47 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "constants.h"

unsigned DC = 0;
static unsigned short dataSegment[SEGMENT_MAXIMUM_SIZE];

unsigned getDC() {
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