/* 
 * File:   hash.h
 * Author: dorons
 *
 * Created on March 1, 2010, 8:29 PM
 */

#ifndef _HASH_H
#define	_HASH_H

#ifndef _ERRORHANDLER_H
#include "errorHandler.h"
#endif

#define HASHSIZE 100

typedef struct node{
    char* name;
    unsigned data;
    struct node* next;
}hashNode;

unsigned hashVal(const char*);
errorCode addHashNode(hashNode**, char*, unsigned);
errorCode getData(hashNode**, char*, unsigned*);

#endif	/* _HASH_H */

