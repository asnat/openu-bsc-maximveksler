/* 
 * File:   hash.h
 * Author: dorons
 *
 * Created on March 1, 2010, 8:29 PM
 */

#ifndef _HASH_H
#define	_HASH_H

#ifndef _CONSTANTS_H
#include "constants.h"
#endif

#ifndef _INSTRUCTIONSTRUCTURE_H
#include "asmInstruction.h"
#endif

#define HASHSIZE 100

typedef struct node{
    char* name;
    LinkerAddress linkerType;
    unsigned short data;
    hashSegmentType segmentFlag;
    struct node* prev;
    struct node* next;
} hashNode;

unsigned hashVal(const char*);
_bool addHashNode(hashNode**, char*,LinkerAddress, unsigned short, hashSegmentType);
_bool getHashNodeData(hashNode**,const char*, unsigned short*);
void freeHashArray(hashNode**);
LinkerAddress getHashType(hashNode** hashArray, char* nodeName);
hashSegmentType getHashSegmentType(hashNode** labelHashTable, char* labelName);

#endif	/* _HASH_H */

