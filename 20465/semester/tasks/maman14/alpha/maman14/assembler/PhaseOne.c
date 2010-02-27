#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ErrorMessages.h"
#include "AsmInstruction.h"
#include "LineParser.h"

void processAssemblyLine(char *asmCodeLine) {
    AsmInstruction asmInst = parseLine(asmCodeLine);

    if(asmInst->instructionType == INST) {
        // calling the function that matches this command from a function table.
        //commandFunction(asmInst);
    }

}
