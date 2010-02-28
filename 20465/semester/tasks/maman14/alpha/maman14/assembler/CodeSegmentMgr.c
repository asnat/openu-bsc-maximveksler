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
unsigned short codeSegment[SEGMENT_MAXIMUM_SIZE];

int getIC() {
    return IC;
}

void storeData(unsigned short data) {
    codeSegment[IC] = data;

    IC += 1;
}

short* getData() {
    return codeSegment;
}