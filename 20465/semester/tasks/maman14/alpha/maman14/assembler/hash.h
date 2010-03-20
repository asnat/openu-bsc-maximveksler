/* 
 * File:   hash.h
 * Author: dorons
 *
 * Created on March 1, 2010, 8:29 PM
 */

#ifndef _HASH_H
#define	_HASH_H

#include "constants.h"

#define HASHSIZE 100

typedef struct node{
    char* name;
    unsigned data;
    struct node* next;
}hashNode;

unsigned hashVal(const char*);
_bool addHashNode(hashNode**, char*, unsigned);
_bool getHashNodeData(hashNode**,const char*, unsigned*);

#endif	/* _HASH_H */

