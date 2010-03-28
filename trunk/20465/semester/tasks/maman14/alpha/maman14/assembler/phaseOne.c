#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "asmInstruction.h"
#include "asmCommands.h"
#include "lineParser.h"
#include "phaseOne.h"
#include "label.h"

#define PHASE_ONE_DEBUG 1

void processAssemblyLine(const char *asmCodeLine) {
    unsigned short address;
    
    #if PHASE_ONE_DEBUG
        printf("phaseOne.processAssemblyLine [%s]\n", asmCodeLine);
    #endif

    #if PHASE_ONE_DEBUG
        printf("phaseOne.processAssemblyLine - before parser\n");
    #endif
    AsmInstruction asmInst = parseLine(asmCodeLine);

    #if PHASE_ONE_DEBUG
        printf("phaseOne.processAssemblyLine - before process\n");
    #endif
    if(asmInst != NULL) { /* If we get NULL it's a comment hench no processing required */        
        process(asmInst);
        freeAsmInstruction(asmInst);
    }

    printf("processAssemblyLine GETTING DEBUG LABEL\n");
    getLabelAddress((char*) "LOOP", &address);
    printf("processAssemblyLine GOT DEBUG LABEL %d\n", address);

    #if PHASE_ONE_DEBUG
        printf("phaseOne.processAssemblyLine - after process\n");
    #endif

}
