#include <stdio.h>
#include "constants.h"
#include "codeSegmentMgr.h"
#include "dataSegmentMgr.h"
#include "asmInstruction.h"
#include "lineParser.h"
#include "errorHandler.h"
#include "outputFilesHandler.h"
#include "label.h"

#define MAXARG 2


static void addRelocateable(char* operand, AddressingType type){
    unsigned short* address = NULL;

    if ( type == INDIRECT || type == DIRECT) {
        if (getLabelType(operand) == EXTERNAL){
            writeToOutputFile(EXT_FILE, operand, getIC()-(unsigned short) 1);
        }
        else{
            getLabelAddress(operand, address);
            storeCode(*address);
        }
        forward();
    }
    else {
        if ( type == IMMIDIATE )
        forward();
    }
}

_bool phase2processAssemlby(char* asmCodeLine){
    AsmInstruction asmIns = parseLine(asmCodeLine);
    int arg;
    unsigned short* address = NULL;

    switch (asmIns->instructionType){
        case ENTRY:
            if (writeToOutputFile(ENT_FILE, asmIns->instruction->ENTRY.referenceName, getLabelAddress(asmIns->instruction->ENTRY.referenceName, address))){
                return TRUE;
            }
            return FALSE;
            break;
        case INST:
            for (arg=1; arg <= MAXARG; arg++){
                addRelocateable(asmIns->instruction->INST.srcOP, asmIns->instruction->INST.srcOPType);
                addRelocateable(asmIns->instruction->INST.dstOP, asmIns->instruction->INST.dstOPType);
            }
            return TRUE;
            break;
        default:
            return TRUE;
    }
}
