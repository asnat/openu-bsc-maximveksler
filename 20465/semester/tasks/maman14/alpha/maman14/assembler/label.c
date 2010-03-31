#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "errorHandler.h"



static hashNode* labelHashTable[HASHSIZE];

/* init the label table */
void initLabelTable(){
    register int i;

    /* all indexes point to NULL */
    for(i=0; i<HASHSIZE; i++) {
        labelHashTable[i] = NULL;
    }
}

/* return the label linker type */
LinkerAddress getLabelType(char* labelName){
    return getHashType(labelHashTable, labelName);
}

/* free the label table */
void freeLabelTable(){
    freeHashArray(labelHashTable);
}

/* return the label address */
_bool getLabelAddress(char* labelName, unsigned short* data){
    return getHashNodeData(labelHashTable, labelName, data);
}

/* add alabel to label table */
_bool addLabel(char* labelName, LinkerAddress type, unsigned short data, hashSegmentType segment) {
    return addHashNode(labelHashTable, labelName, type, data, segment);
}

_bool getLabelSegmentType(char* labelName){
    return getHashSegmentType(labelHashTable, labelName);
}