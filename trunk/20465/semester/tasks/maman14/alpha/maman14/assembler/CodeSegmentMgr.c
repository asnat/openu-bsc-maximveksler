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

unsigned short storeData(unsigned short data) {
    codeSegment[IC] = data;
    IC += 1;
    
    return codeSegment[IC-1];
}

unsigned short* getData() {
    return codeSegment;
}