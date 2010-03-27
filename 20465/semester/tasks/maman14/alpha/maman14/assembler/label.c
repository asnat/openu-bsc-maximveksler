#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "errorHandler.h"
#include "constants.h"

static hashNode** labelHashTable;

void initLabelTable(){
    register int i;
    labelHashTable = (hashNode**) malloc(HASHSIZE*sizeof(hashNode*));
    for(i=0;i<HASHSIZE;i++)
        *(labelHashTable+i)=NULL;
}

void freeLabelTable(){
    freeHashArray(labelHashTable);
}

_bool getLabelAddress(char* labelName, unsigned short* data){
    return getHashNodeData(labelHashTable, labelName, data);
}

_bool addLabel(char* labelName, unsigned short data){
    return addHashNode(labelHashTable, labelName, data);
}