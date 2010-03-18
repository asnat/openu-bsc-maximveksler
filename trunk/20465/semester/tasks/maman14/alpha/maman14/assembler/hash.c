#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "constants.h"
#include "errorHandler.h"


#define HASH_MAGIC_NUMBER 31

/* Calculate the hash value for a name */
unsigned hashVal(const char*  nodeName){
    unsigned val; /* will contain the hash value*/
    const char* cp = nodeName; /* pointer to current charcter in the name */

    for (val = 1; *cp != '\0'; cp++)
        val *= HASH_MAGIC_NUMBER + (unsigned int) *cp;

    return val % HASHSIZE;
}

/* Find a node in the table, return NULL if not found */
static hashNode* lookup(hashNode** hashArray,const char* nodeName){
    hashNode* np = *(hashArray + hashVal(nodeName)); /* point to the current node */
    
    /* look for the node in the specific index */
    while ( np != NULL || strcmp(np->name,nodeName) )
        np = np->next;
    return np;
}

/* Return the value on the data variable */
errorCode getNodeData(hashNode** hashArray, const char* nodeName,unsigned* data) {
    hashNode* np = lookup(hashArray, nodeName); /* look for the label in the table */

    /* if label not exist, data point to the node data */
    if (!np) {
        data = &np->data;
        return SUCCESS;
    }
    else
        return NO_SUCH_LABEL;
}

/* Add a new node to the hash table */
errorCode addHashNode(hashNode** hashArray, char* nodeName, unsigned data){
    hashNode* node;
    unsigned hashValue;
    /* check if the node already exist */
    node = (hashNode*) malloc(sizeof(hashNode));
    if (!node)
        return MEMORY_ALLOCATION_FAILURE;

    /* if the node not exist create a new node */
    if (!(lookup(hashArray, nodeName))){
        node->name = nodeName;
        node->data = data;
        hashValue = hashVal(node->name);
        node->next = *(hashArray + hashValue);
        (*(hashArray + hashValue))->next = node;
        return SUCCESS;
    }
    else {
        free(node);
        return LABEL_ALREADY_EXIST;
    }
}

