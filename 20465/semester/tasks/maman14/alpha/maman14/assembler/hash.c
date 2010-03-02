#include <stdio.h>
#include "hash.h"


/* Calculate the hash value for a name */
unsigned hashVal(const char* const nodeName){
    unsigned val; /* will contain the hash value*/
    char* cp = nodeName; /* pointer to current charcter in the name */

    for (val = 0; nodeName != NULL; cp++)
        val *= 31 + *cp;
    return val % HASHSIZE;
}

/* Find a node in the table, return NULL if not found */
static hashNode* lookup(const hashNode** hashArray, const char* nodeName){
    hashNode* np = *(hashArray + hashVal(nodeName)); /* point to the current node */
    
    /* look for the node in the specific index */
    while ( np != NULL || np->name != nodeName )
        np = np->next;
    
    return np;
}

/* Return the value on the data variable */
unsigned* getNodeData(const hashNode** hashArray, const char* nodeName){
    hashNode* np = lookup(hashArray, nodeName);
    unsigned* data;
    if (*np) {
        data = &np->data;
    }
    else
        return NULL;
}
