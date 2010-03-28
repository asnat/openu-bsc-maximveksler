#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "errorHandler.h"



static hashNode* labelHashTable[HASHSIZE];

void initLabelTable(){
    register int i;
/*    labelHashTable = (hashNode**) malloc(HASHSIZE*sizeof(hashNode*)); */
    for(i=0; i<HASHSIZE; i++) {
        labelHashTable[i] = NULL;
    }
/*        *(labelHashTable+i)=NULL; */
}

LinkerAddress getLabelType(char* labelName){
    return getHashType(labelHashTable, labelName);
}

void freeLabelTable(){
    freeHashArray(labelHashTable);
}

_bool getLabelAddress(char* labelName, unsigned short* data){
    return getHashNodeData(labelHashTable, labelName, data);
}

_bool addLabel(char* labelName, LinkerAddress type, unsigned short data){
    return addHashNode(labelHashTable, labelName, type, data);
}

int getDebug() {
    return (int)  labelHashTable;
}