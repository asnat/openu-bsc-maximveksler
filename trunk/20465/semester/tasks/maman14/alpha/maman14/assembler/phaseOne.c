#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "asmInstruction.h"
#include "asmCommands.h"
#include "lineParser.h"
#include "phaseOne.h"

void processAssemblyLine(const char *asmCodeLine) {
    AsmInstruction asmInst = parseLine(asmCodeLine);

    if(asmInst != NULL) { /* If we get NULL it's a comment hench no processing required */        
        process(asmInst);
        freeAsmInstruction(asmInst);
    }
}
