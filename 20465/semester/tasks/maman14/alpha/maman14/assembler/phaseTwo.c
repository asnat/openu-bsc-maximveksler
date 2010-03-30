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

/* process relocateable lines instruction line*/
static void addRelocateable(char* operand, AddressingType type){
    unsigned short address;

    /* process INDIRECT and DIRECT argument */
    if ( type == INDIRECT || type == DIRECT) {
        /* if the label external, change the linker type of the line to EXTERNAL and add the label to the ext file */
        if (getLabelType(operand) == EXTERNAL){
            storeCode(0,EXTERNAL);
            writeToOutputFile(EXT_FILE, operand, getIC()-(unsigned short) 1);
        }

        /* if the label is not external store the address in the code segment */
        else{
            getLabelAddress(operand, &address);
            storeCode(address, UNKNOWN_TYPE);
        }
    }
    else {
        /* if IMMIDIATE, phase one handled it already */
        if ( type == IMMIDIATE )
        forward();
    }
}

/* phase 2 line processing, and update the code and data segments*/
_bool phase2processAssemlby(char* asmCodeLine){
    AsmInstruction asmIns = parseLine(asmCodeLine);
    unsigned short address;

    /* process the line only if there is something to process */
    if(asmIns != NULL) {
        switch (asmIns->instructionType){

            /* process entry instuction */
            case ENTRY:
                /* write the entry label name and address to the entry file */
                if (writeToOutputFile(ENT_FILE, asmIns->instruction->ENTRY.referenceName,
                        getLabelAddress(asmIns->instruction->ENTRY.referenceName, &address))){
                    return TRUE;
                }
                return FALSE;
                break;

            /* process assembly instruction*/
            case INST:

                forward();
                /* process first argument */
                addRelocateable(asmIns->instruction->INST.srcOP, asmIns->instruction->INST.srcOPType);
                /* process second argument */
                addRelocateable(asmIns->instruction->INST.dstOP, asmIns->instruction->INST.dstOPType);
                
                return TRUE;
                break;

            default:
                return TRUE;
        }
    }
    return TRUE;
}
