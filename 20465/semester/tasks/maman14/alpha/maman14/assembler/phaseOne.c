#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "asmInstruction.h"
#include "asmCommands.h"
#include "lineParser.h"
#include "phaseOne.h"

void processAssemblyLine(char *asmCodeLine) {
    AsmInstruction asmInst = parseLine(asmCodeLine);

    if(asmInst->instructionType == INST) {
        process(asmInst);
    }

    freeAsmInstruction(asmInst);
}
