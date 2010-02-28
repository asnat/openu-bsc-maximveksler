#include "AsmInstruction.h"
#include "CodeSegmentMgr.h"

static void storeToCodeSegment(unsigned short dstRgstrCode, unsigned short dstAddrTypeCode,
                               unsigned short srcRgstrCode, unsigned short srcAddrTypeCode,
                               unsigned short instCode) {

    unsigned short instruction = 0;

    instruction = dstRgstrCode;
    instruction &= (dstAddrTypeCode << 3);
    instruction &= (srcRgstrCode << 6);
    instruction &= (srcAddrTypeCode << 9);
    instruction &= (instCode << 12);

    storeData(instruction);
}

void* cmdLookupTable(char* commandName) {
    /*
    while(bla bla bla, not null) {
        if found cmd
            return function address;
    }

     return null;
     */
}

void mov(AsmInstruction asmInst) {
    short instructionCode = 0;
    // verify has 2 operands.
    // verify addressing methods are valid.

    //storeToCodeSegment();
}


