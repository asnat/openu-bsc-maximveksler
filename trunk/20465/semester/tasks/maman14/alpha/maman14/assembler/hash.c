#include <stdio.h>
#include "hash.h"

/* Find a node in the table */
static hashNode* lookup(const hashNode** hashArray, const char* nodeName){
    hashNode* np; /* point to the requested node */
    /*
    for (np = )
    */
    return np;
}

/* Calculate the hash value for a name */
unsigned hashVal(const char* const nodeName){
    unsigned val; /* will contain the hash value*/
    char* cp = nodeName; /* pointer to current charcter in the name */

    for (val = 0; nodeName != NULL; cp++)
        val *= 31 + *cp;
    return val % HASHSIZE;
}


