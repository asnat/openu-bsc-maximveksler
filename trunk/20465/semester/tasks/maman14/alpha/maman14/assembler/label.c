#include <stdio.h>
#include "hash.h"
#include "constants.h"

static hashNode* labelHashTable[HASHSIZE];

void initLabelTable(void){
    register int i;
    for(i=0;i<HASHSIZE;i++)
        labelHashTable[i]=NULL;
}

unsigned getLabelAddress(char* labelName){
    /* return getNodeData(labelHashTable,labelName); */
    return 0;
}

void addLabel(char labelName){

}