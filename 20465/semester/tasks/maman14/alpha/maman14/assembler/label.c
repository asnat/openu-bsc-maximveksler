#include <stdio.h>
#include "hash.h"
#include "errorHandler.h"

static hashNode* labelHashTable[HASHSIZE];

void initLabelTable(void){
    register int i;
    for(i=0;i<HASHSIZE;i++)
        labelHashTable[i]=NULL;
}

errorCode getLabelAddress(char* labelName, unsigned* data){
    return getData(labelHashTable, labelName, data);
}

errorCode addLabel(char* labelName, unsigned data){
    return addHashNode(labelHashTable, labelName, data);
}