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
static hashNode* lookup(hashNode** hashArray, const char* nodeName){
    hashNode* np = *(hashArray + hashVal(nodeName)); /* point to the current node */

    /* look for the node in the specific index */
    while (np != NULL && strcmp(np->name, nodeName)) {
        np = np->next;
    }
    
    return np;
}





/* Return the value on the data variable */
_bool getHashNodeData(hashNode** hashArray, const char* nodeName, unsigned short* data) {
    hashNode* np = lookup(hashArray, nodeName); /* look for the label in the table */
    _bool rc = FALSE; /* return code */

    /* if label exist, data point to the node data */
    if (np) {
        *data = np->data;
        rc = TRUE;
    }
    else
        setErrorCode(NO_SUCH_LABEL);

    return rc;
}





/* Add a new node to the hash table */
_bool addHashNode(hashNode** hashArray, char* nodeName, LinkerAddress type, unsigned short data, hashSegmentType segment){
    hashNode* node;
    unsigned hashValue;

    /* see if node with the same name exist */
    if (!(lookup(hashArray, nodeName))) {

        /* if the node doesnt exist create a new node */
        node = (hashNode*) malloc(sizeof(hashNode));
        if (!node) {
            setErrorCode(MEMORY_ALLOCATION_FAILURE);
            return FALSE;
        }
        node->name = (char*) malloc(strlen(nodeName)*sizeof(char) + 1);
        strcpy(node->name, nodeName);
        node->linkerType = type;
        node->data = data;
        node->segmentFlag = segment;
        hashValue = hashVal(node->name);
        node->prev = NULL;
  
        if(*(hashArray + hashValue) != NULL) {
            (*(hashArray + hashValue))->prev = node;
        }
        
        node->next = *(hashArray + hashValue);
        *(hashArray + hashValue) = node;

        return TRUE;
    } else {
        setErrorCode(LABEL_ALREADY_EXIST);
        return FALSE;
    }
}






/* free the Hash table*/
void freeHashArray(hashNode** hashArray){
    hashNode* currentNode;
    hashNode* next;

    int hashIndex;


    for (hashIndex = 0; hashIndex<HASHSIZE; hashIndex++){
        currentNode = hashArray[hashIndex];

        while(currentNode != NULL) {
            /* Store the next node */
            next = currentNode->next;

            /* Free current node name */
            if(currentNode->name != NULL)
                free(currentNode->name);

            /* Free current node */
            free(currentNode);

            /* Update pointer to the next node */
            currentNode = next;
        }
    }
}







/* get the node linker type */
LinkerAddress getHashType(hashNode** hashArray, char* nodeName){
    hashNode* node = lookup(hashArray, nodeName);
    if (node != NULL)
        return node->linkerType;
    else
        return UNKNOWN_TYPE;
}





hashSegmentType getHashSegmentType(hashNode** hashArray , char* nodeName){
    hashNode* node = lookup(hashArray, nodeName);

    if (node != NULL)
        return node->segmentFlag;
    else
        return UNKNOWN_SEG;
}