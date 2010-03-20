/* 
 * File:   LineParser.c
 * Author: hq4ever
 *
 * Created on February 27, 2010, 7:00 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "asmInstruction.h"
#include "lineParser.h"
#include "errorHandler.h"
#include "stringUtil.h"
#include "constants.h"

/*
 * 
 */
AsmInstruction parseLine(const char* line) {
    unsigned int index = 0;

    unsigned int labelFrom = 0;
    unsigned int labelTo = 0;

    unsigned int cmdFrom = 0;
    unsigned int cmdTo = 0;

    unsigned int srcOPFrom = 0;
    unsigned int srcOPTo = 0;

    unsigned int dstOPFrom = 0;
    unsigned int dstOPTo = 0;

    unsigned int declFrom = 0;
    unsigned int declTo = 0;

    unsigned int declDataFrom = 0;
    unsigned int declDataTo = 0;

    
    if(line[index] == ';') {
        /* Line is comment, we don't waste time on nonsense */
        return NULL;
    }

    /* First seek to see if we have a lable */
    if(!isspace(line[index])) {
        /* First char is not space, can be label */
        if(isalpha(line[index])) {
            /* First char is alpha, goot */
            
            while(isalnum(line[++index])); /* Forward all legal lable chars */
            if(line[index] == ':') {
                /* Yay, it really is a label */
                labelFrom = 0;
                labelTo = index; /* Keep in mind that we store "TO" locations in up to but not including form */

                index++;
            } else {
                /* We don't know and don't care what is was, just reset the index... */
                index = 0;
            }
        }
    }

    /* Clear any white space */
    if(isspace(line[index])) {
        while(isspace(line[++index]));

        if(line[index] == '\0')
            return NULL; /* It was a line full of white space */
    }

    if(line[index] == '.') {
        /* Declaration */
        declFrom = ++index;

        if(!isalnum(line[index])) {
            /* Legal lable starts with alnum */

            /* TODO: ERROR not valid declaration format */
            return NULL;
        }
        while(isalnum(line[++index])); /* consum all alnum legal chars */

        declTo = index; /* Store where declaration instruction name ends */

        if(!isspace(line[index])) { /* After instruction name there should be space seperator */
            /* TODO: ERROR not valid declaration format */
            return NULL;
        }
        while(isspace(line[++index])); /* Good, valid label syntax - Consume all space chars */


        if(!isgraph(line[index])) {
            /* TODO: ERROR Missing declaration data  */
            return NULL;
        }
        declDataFrom = index;

        while(isgraph(line[++index])); /* Consume all legal data chars */

        if(line[index] != '\0') {
            /* TODO: ERROR Too many parameters for declaration */
            return NULL;
        }
        declDataTo = index;

        /* return allocDeclarationInstruction... */
    } else if (isalpha(line[index])){
        /* Command */
        cmdFrom = index;

        while(isalpha(line[++index])); /* Consume cmd chars */
        cmdTo = index;
        
        if(line[index] == '\0') {
            return allocAsmInstructionINST(line, labelFrom, labelTo, cmdFrom, cmdTo, srcOPFrom, srcOPTo, dstOPFrom, dstOPTo);
        } else if(!isspace(line[index])) {
            /* TODO: Error illigal char in command*/
            return NULL;
        }

        while(isspace(line[++index]));

        if(!isalpha(line[index]) && line[index] != '@' && line[index] != '#') {
            /* TODO: Error illigal char in command*/
            return NULL;
        }
        srcOPFrom = index;

        while (isalnum(line[++index]));
        srcOPTo = index;

        if(isspace(line[index])) {
            while(isspace(line[++index])); /* after first operand it's possible that we will have whitespace */
        }

        if(line[index] == '\0') {
            return allocAsmInstructionINST(line, labelFrom, labelTo, cmdFrom, cmdTo, srcOPFrom, srcOPTo, dstOPFrom, dstOPTo);
        } else if(line[index] == ',') {
            /* Skip, legal char */
            index++;
        } else {
            /* TODO: Error illigal char in command*/
            return NULL;
        }

        if(isspace(line[index])) {
            while(isspace(line[++index])); /* whitespace between "," and second operand */
        }

        if(!isalpha(line[index]) && line[index] != '@' && line[index] != '#') {
            /* TODO: Error illigal char in command*/
            return NULL;
        }
        dstOPFrom = index;

        while (isalnum(line[++index]));
        
        if(!line[index] == '\0') {
            /* TODO: Error illigal char in command*/
            return NULL;
        }
        
        dstOPTo = index;

        return allocAsmInstructionINST(line, labelFrom, labelTo, cmdFrom, cmdTo, srcOPFrom, srcOPTo, dstOPFrom, dstOPTo);
    } else {
        /* TODO: ERROR Invalid assembly syntax */
        return NULL;
    }


    return NULL; /* We should never reach here */
}

/* TOOD: This is public only for testing, after all is working this should
    become static and only be called from parseLine */
AsmInstruction allocAsmInstructionINST(
        const char* line,
        const unsigned int labelFrom, const unsigned int labelTo,
        const unsigned int cmdFrom, const unsigned int cmdTo,
        const unsigned int srcOPFrom, const unsigned int srcOPTo,
        const unsigned int dstOPFrom, const unsigned int dstOPTo
        ) {

    int helperI;
    
    AsmInstruction asmInstruction = (AsmInstruction) malloc(sizeof(struct AsmInstruction));
    if(asmInstruction == NULL) {
        fatalError(MEMORY_ALLOCATION_FAILURE, "Can't allocate memory for AsmInstruction");
    }

    asmInstruction->instruction = malloc(sizeof(union InstructionUnion));
    if(asmInstruction->instruction == NULL) {
        fatalError(MEMORY_ALLOCATION_FAILURE, "Can't allocate memory for InstructionUnion");
    }

    asmInstruction->instructionType = INST;

    /* String operations */
    asmInstruction->label = substr(line, labelFrom, labelTo);
    asmInstruction->instruction->INST.command = substr(line, cmdFrom, cmdTo);

    if(line[srcOPFrom] == '#') {
        asmInstruction->instruction->INST.srcOP = substr(line, srcOPFrom+1, srcOPTo);
        asmInstruction->instruction->INST.srcOPType = IMMIDIATE;

        if(asmInstruction->instruction->INST.srcOP[0] != '+'
                && asmInstruction->instruction->INST.srcOP[0] != '-'
                && !isdigit(asmInstruction->instruction->INST.srcOP[0])) {

            /* TODO: ERROR Source operand is not a valid number */
            freeAsmInstruction(asmInstruction);
            return NULL;
        }

        helperI = 0;
        while(isdigit(asmInstruction->instruction->INST.srcOP[++helperI]));

        if(asmInstruction->instruction->INST.srcOP[helperI] != '\0') {
            /* TODO: ERROR Source operand is not a valid number */
            freeAsmInstruction(asmInstruction);
            return NULL;
        }

        /* Reaching here means we have a valid IMMIDIATE direction */
    } else if (line[srcOPFrom] == '@') {
        asmInstruction->instruction->INST.srcOP = substr(line, srcOPFrom+1, srcOPTo);
        asmInstruction->instruction->INST.srcOPType = INDIRECT;

        helperI = 0;
        if(!isalpha(asmInstruction->instruction->INST.srcOP[0])) {
            /* TODO: ERROR source operand is not a valid INDIRECT notation */
            freeAsmInstruction(asmInstruction);
            return NULL;
        }

        while(isalnum(asmInstruction->instruction->INST.srcOP[++helperI]));
        if(asmInstruction->instruction->INST.srcOP[helperI] != '\0') {
            /* TODO: ERROR source operand is not a valid INDIRECT notation */
            freeAsmInstruction(asmInstruction);
            return NULL;
        }
        
         /* Reaching here means we have a valid INDIRECT direction */
    } else if (line[srcOPFrom] == 'r' && (srcOPTo - srcOPFrom) == 2) { /* Register is length 2 and starts with small "r" */
        asmInstruction->instruction->INST.srcOP = substr(line, srcOPFrom, srcOPTo);
        asmInstruction->instruction->INST.srcOPType = REGISTER;

        if(asmInstruction->instruction->INST.srcOP[1] > '7' || asmInstruction->instruction->INST.srcOP[1] < '0') {
            /* TODO: ERROR source operand is not a valid REGISTER notation */
            freeAsmInstruction(asmInstruction);
            return NULL;
        }

         /* Reaching here means we have a valid REGISTER direction */
    } else {
        asmInstruction->instruction->INST.srcOP = substr(line, srcOPFrom, srcOPTo);
        asmInstruction->instruction->INST.srcOPType = DIRECT;

        helperI = 0;
        if(!isalpha(asmInstruction->instruction->INST.srcOP[0])) {
            /* TODO: ERROR source operand is not a valid DIRECT notation */
            freeAsmInstruction(asmInstruction);
            return NULL;
        }

        while(isalnum(asmInstruction->instruction->INST.srcOP[++helperI]));
        if(asmInstruction->instruction->INST.srcOP[helperI] != '\0') {
            /* TODO: ERROR source operand is not a valid DIRECT notation */
            freeAsmInstruction(asmInstruction);
            return NULL;
        }
        
         /* Reaching here means we have a valid DIRECT direction */
    }

    asmInstruction->instruction->INST.dstOP = substr(line, dstOPFrom, dstOPTo);

    /* Command addressing types */
/*    asmInstruction->instruction->INST.srcOPType = srcOPType;
    asmInstruction->instruction->INST.dstOPType = dstOPType;
 */

    return asmInstruction;
}

void freeAsmInstruction(AsmInstruction asmInst) {
    /*
     * TODO: Free the whole asmInst memory model...
     * this means go into each and every sub struct, sub union,
     * see what was allocated on the heap and kick it from the
     * memory table, otherwise you have memory leaks, which has
     * direct corelation to the final grade.
     */
    asmInst = asmInst;
}