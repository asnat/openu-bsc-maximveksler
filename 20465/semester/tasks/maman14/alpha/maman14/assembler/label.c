#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "errorHandler.h"
#include "constants.h"

static hashNode** labelHashTable;

void initLabelTable(void){
    register int i;
    labelHashTable = (hashNode**) malloc(HASHSIZE*sizeof(hashNode*));
    for(i=0;i<HASHSIZE;i++)
        *(labelHashTable+i)=NULL;
}

_bool getLabelAddress(char* labelName, unsigned* data){
    return getHashNodeData(labelHashTable, labelName, data);
}

_bool addLabel(char* labelName, unsigned data){
    return addHashNode(labelHashTable, labelName, data);
}