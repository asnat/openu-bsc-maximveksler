#include <stdio.h>
#include "hash.h"
#include "constants.h"

static hashNode* labelHashTable[HASHSIZE];

_bool getLabelAddress(unsigned* address, char* labelName){
    unsigned* address;
    _bool labelExist;

    if (address = getNodeData(labelHashTable,labelName))
        labelExist = true;
    else
        labelExist = false;
    return labelExist;
}


