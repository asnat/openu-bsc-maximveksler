#include "hash.h"

static hashNode* labelHashTable[HASHSIZE];

unsigned getLabelAddress(char* labelName){
    return getNodeData(labelHashTable,labelName);
}


