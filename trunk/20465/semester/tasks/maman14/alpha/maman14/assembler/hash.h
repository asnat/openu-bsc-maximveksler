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

#define HASHSIZE 100

typedef struct node{
    char* name;
    unsigned short data;
    struct node* prev;
    struct node* next;
}hashNode;

unsigned hashVal(const char*);
_bool addHashNode(hashNode**, char*, unsigned short);
_bool getHashNodeData(hashNode**,const char*, unsigned short*);
void freeHashArray(hashNode**);

#endif	/* _HASH_H */

