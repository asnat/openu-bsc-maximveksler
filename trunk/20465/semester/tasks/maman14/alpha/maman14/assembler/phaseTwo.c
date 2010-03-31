#include <stdio.h>
#include "constants.h"
#include "codeSegmentMgr.h"
#include "dataSegmentMgr.h"
#include "asmInstruction.h"
#include "lineParser.h"
#include "errorHandler.h"
#include "outputFilesHandler.h"
#include "label.h"
#include "hash.h"

#define MAXARG 2

/* process relocateable lines instruction line*/
static void addRelocateable(char* operand, AddressingType type, unsigned short endCodeSeg){
    unsigned short address;
    LinkerAddress labelLinkerAddress;
    hashSegmentType labelSegment;

    /* process INDIRECT and DIRECT argument */
    if ( type == INDIRECT || type == DIRECT) {
        /* if the label external, change the linker type of the line to EXTERNAL and add the label to the ext file */
        if ((labelLinkerAddress = getLabelType(operand)) == EXTERNAL){
            storeCode(0,EXTERNAL);
            writeToOutputFile(EXT_FILE, operand, getIC()-(unsigned short) 1);
        }

        /* if the label is not external store the address in the code segment */
        else if(labelLinkerAddress == RELOCATBLE){
            getLabelAddress(operand, &address);
            labelSegment = getLabelSegmentType(operand);
            if (labelSegment == CODE_SEG){
                storeCode(address , UNKNOWN_TYPE);
            }
            else if (labelSegment == DATA_SEG){
                storeCode(address + (endCodeSeg -1) , UNKNOWN_TYPE);
            }
            else
                handleError(UNKNOWN_SEGMENT_TYPE, NULL);
        }
        else{
            handleError(NO_SUCH_LABEL, operand);
        }
    }
    else {
        /* if IMMIDIATE, phase one handled it already */
        if ( type == IMMIDIATE )
            forward();
    }
}

/* phase 2 line processing, and update the code and data segments*/
_bool phase2processAssemlby(char* asmCodeLine, unsigned short endCodeSeg){
    AsmInstruction asmIns = parseLine(asmCodeLine);
    unsigned short address;
    hashSegmentType labelSegment;

    /* process the line only if there is something to process */
    if(asmIns != NULL) {
        switch (asmIns->instructionType){

            /* process entry instuction */
            case ENTRY:
                if(getLabelAddress(asmIns->instruction->ENTRY.referenceName, &address)){
                /* write the entry label name and address to the entry file */
                    labelSegment = getLabelSegmentType(asmIns->instruction->ENTRY.referenceName);
                    if (labelSegment == CODE_SEG){
                        if (writeToOutputFile(ENT_FILE, asmIns->instruction->ENTRY.referenceName,address)){
                            return TRUE;
                        }
                    }
                    else if (labelSegment == DATA_SEG){
                        if (writeToOutputFile(ENT_FILE, asmIns->instruction->ENTRY.referenceName,address + endCodeSeg-1)){
                            return TRUE;
                        }
                    }
                    else
                        handleError(UNKNOWN_SEGMENT_TYPE, NULL);
                }
                return FALSE;
                break;

            /* process assembly instruction*/
            case INST:

                forward();
                /* process first argument */
                addRelocateable(asmIns->instruction->INST.dstOP, asmIns->instruction->INST.dstOPType, endCodeSeg);
                /* process second argument */
                addRelocateable(asmIns->instruction->INST.srcOP, asmIns->instruction->INST.srcOPType, endCodeSeg);
                
                return TRUE;
                break;

            default:
                return TRUE;
        }
    }
    return TRUE;
}
