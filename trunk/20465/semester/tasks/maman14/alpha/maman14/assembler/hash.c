#include <stdio.h>
#include "hash.h"
#include "constants.h"

/* Calculate the hash value for a name */
unsigned hashVal(char*  nodeName){
    unsigned val; /* will contain the hash value*/
    char* cp = nodeName; /* pointer to current charcter in the name */

    for (val = 0; nodeName != NULL; cp++)
        val *= 31 + *cp;
    return val % HASHSIZE;
}

/* Find a node in the table, return NULL if not found */
static hashNode* lookup(hashNode** hashArray,char* nodeName){
    hashNode* np = *(hashArray + hashVal(nodeName)); /* point to the current node */
    
    /* look for the node in the specific index */
    while ( np != NULL || np->name != nodeName )
        np = np->next;
    
    return np;
}

/* Return the value on the data variable */
/*unsigned getNodeData(hashNode** hashArray, char* nodeName){
    hashNode* np = lookup(hashArray, nodeName);
    if (*np) {
        return np->data;
    }
    else
        return NULL;
}*/
