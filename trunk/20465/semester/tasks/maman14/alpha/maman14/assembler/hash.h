/* 
 * File:   hash.h
 * Author: dorons
 *
 * Created on March 1, 2010, 8:29 PM
 */

#ifndef _HASH_H
#define	_HASH_H

#define HASHSIZE 100

typedef struct node {
    char* name;
    int data;
    node* next;
}hashNode;

unsigned hashVal(const char*);
short int addNode(hashNode**,const char*,const int);
char* getData(char*);

#endif	/* _HASH_H */

