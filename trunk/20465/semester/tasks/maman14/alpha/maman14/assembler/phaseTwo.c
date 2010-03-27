#include <stdio.h>
#include "constants.h"
#include "codeSegmentMgr.h"
/* #include dataSegmentMgr.h */
#include "asmInstruction.h"
#include "lineParser.h"
#include "errorHandler.h"
#include "outputFilesHandler.h"

#define LINE_LENGTH 81

/* _bool phaseTwo(FILE* currentFileHamdler){
    char fc, line[LINE_LENGTH], linkerLineType[SEGMENT_MAXIMUM_SIZE];
    int lineIndex=0;
    AsmInstruction instructionLine;

    
    if(!writeObjectFileFirstRow())
        fatalError(2,"moreInfo");
     setIC(0);
     setDC(0);

    while ((fc = fgetc(currentFileHamdler)) != EOF){
        if (fc != '\n'){
            line[lineIndex++] = fc;
        }
        instructionLine = parseLine(line);
        if (InstructionLine)
    }
} */
