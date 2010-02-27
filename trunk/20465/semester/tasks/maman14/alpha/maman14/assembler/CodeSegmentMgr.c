/* 
 * File:   CodeSegmentMgr.c
 * Author: hq4ever
 *
 * Created on February 27, 2010, 10:47 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "Constants.h"

int IC = 0;
short codeSegment[SEGMENT_MAXIMUM_SIZE];

int getIC() {
    return IC;
}

void storeData(short* data, int length) {
    // copy from data to our array.

    IC += length;
}

short* getData() {
    return codeSegment;
}