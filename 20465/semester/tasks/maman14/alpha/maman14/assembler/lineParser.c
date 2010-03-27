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
#include "hash.h"

#define STRING_DEC "string"
#define DATA_DEC "data"
#define ENTRY_DEC "entry"
#define EXTERN_DEC "extern"

/*
 * Gets input line which is assembly code line and builds AsmInstruction struct from it.
 * strings that go into each field should be pre calculated.
 */
static AsmInstruction allocAsmInstructionINST(
        const char* line,
        const unsigned int labelFrom, const unsigned int labelTo,
        const unsigned int cmdFrom, const unsigned int cmdTo,
        const unsigned int srcOPFrom, const unsigned int srcOPTo,
        const unsigned int dstOPFrom, const unsigned int dstOPTo
        );

/* Construct DEF AsmInstruction from parsed command line */
static AsmInstruction allocAsmInstructionDEF(
        const char* line,
        const unsigned int labelFrom, const unsigned int labelTo,
        const unsigned int declFrom, const unsigned int declTo,
        const unsigned int declDataFrom, const unsigned int declDataTo
        );

/*
 * Gets unparsed string represnting asm instructions, parses it and calls
 * proper function to create matching structure.
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

    /* First seek to see if we have a label */
    if(!isspace(line[index])) {
        /* First char is not space, can be label */
        if(isalpha(line[index])) {
            /* First char is alpha, goot */
            
            while(isalnum(line[++index])) /* Consume all legal label chars */
                ;
            
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

        if(!isalpha(line[index])) {
            /* Legal declaration starts with isalpha */

            handleError(INVALID_DECLARATION_FORMAT, line + declFrom);
            return NULL;
        }
        while(isalnum(line[++index])); /* consum all alnum legal chars */

        declTo = index; /* Store where declaration instruction name ends */

        if(!isspace(line[index])) { /* After instruction name there should be space seperator */

            handleError(INVALID_DECLARATION_FORMAT, line + declTo);
            return NULL;
        } else {
            while(isspace(line[++index])); /* Good, valid label syntax - Consume all space chars */
        }

        /* as for declaration data it can be pretty much any character... */
        if(!isgraph(line[index])) {
            
            handleError(MISSING_DECLARATION_DATA, line + index);
            return NULL;
        }
        declDataFrom = index;

        while(line[++index] != '\0'); /* Consume all legal data chars */

        declDataTo = index;

        return allocAsmInstructionDEF(line, labelFrom, labelTo, declFrom, declTo, declDataFrom, declDataTo);
    } else if (isalpha(line[index])){
        /* Command */
        cmdFrom = index;

        while(isalpha(line[++index])); /* Consume cmd chars */
        cmdTo = index;
        
        if(line[index] == '\0') {
            return allocAsmInstructionINST(line, labelFrom, labelTo, cmdFrom, cmdTo, srcOPFrom, srcOPTo, dstOPFrom, dstOPTo);
        } else if(!isspace(line[index])) {

            handleError(ILEGAL_CHARACTER_IN_COMMAND, line + index);
            return NULL;
        }

        while(isspace(line[++index]));

        if(!isalpha(line[index]) && line[index] != '@' && line[index] != '#') {

            handleError(ILEGAL_CHARACTER_IN_COMMAND, line + index);
            return NULL;
        }
        srcOPFrom = index;

        while (isalnum(line[++index]) || (line[index] == '-' || line[index] == '+'));
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
            
            handleError(ILEGAL_CHARACTER_IN_COMMAND, line + index);
            return NULL;
        }

        if(isspace(line[index])) {
            while(isspace(line[++index])); /* whitespace between "," and second operand */
        }

        if(!isalpha(line[index]) && line[index] != '@' && line[index] != '#') {
            
            handleError(ILEGAL_CHARACTER_IN_COMMAND, line + index);
            return NULL;
        }
        dstOPFrom = index;

        while (isalnum(line[++index]) || (line[index] == '-' || line[index] == '+'));
        
        dstOPTo = index;

        if(!line[index] == '\0') {
            
            handleError(ILEGAL_CHARACTER_IN_COMMAND, line + index);
            return NULL;
        }
        
        return allocAsmInstructionINST(line, labelFrom, labelTo, cmdFrom, cmdTo, srcOPFrom, srcOPTo, dstOPFrom, dstOPTo);
    } else {

        handleError(INVALID_ASSEMBLY_SYNTAX, NULL);
        return NULL;
    }


    return NULL; /* We should never reach here */
}

static _bool parseOperand(const char* line, unsigned int opFrom, unsigned int opTo,
        char **op, AddressingType* opType) {

    unsigned int helperI = 0;

    if(line[opFrom] == '#') {
        *op = substr(line, opFrom+1, opTo);

        if(*op == NULL) {
            handleError(OPERAND_IS_NOT_VALID_NUMBER, NULL);
        }
        
        *opType = IMMIDIATE;

        if(**op != '+' && **op != '-' && !isdigit(**op)) {

            handleError(OPERAND_IS_NOT_VALID_NUMBER, *op);
            return FALSE;
        }

        helperI = 0;
        while(isdigit(*((*op) + ++helperI)));

        if(*((*op) + helperI) != '\0') {
            
            handleError(OPERAND_IS_NOT_VALID_NUMBER, (*op) + helperI);
            return FALSE;
        }
        /* Reaching here means we have a valid IMMIDIATE direction */
    } else if (line[opFrom] == '@') {
        *op = substr(line, opFrom+1, opTo);

        if(*op == NULL) {
            handleError(INVALID_INDIRECT_NOTATION, NULL);
        }

        *opType = INDIRECT;

        if(!isalpha(**op)) {

            handleError(INVALID_INDIRECT_NOTATION, *op);
            return FALSE;
        }

        while(isalnum(*((*op) + ++helperI)));
        if(*((*op) + helperI) != '\0') {

            handleError(INVALID_INDIRECT_NOTATION, ((*op) + ++helperI));
            return FALSE;
        }
        /* Reaching here means we have a valid INDIRECT direction */  
    } else if (line[opFrom] == 'r' && (opTo - opFrom) == 2) { /* Register is length 2 and starts with small "r" */
        *op = substr(line, opFrom, opTo);

        if(*op == NULL) {
            handleError(INVALID_REGISTER_NOTATION, NULL);
        }

        *opType = REGISTER;

        if(*((*op) + 1) > '7' || *((*op) + 1) < '0') {

            handleError(INVALID_REGISTER_NOTATION, *op);
            return FALSE;
        }

         /* Reaching here means we have a valid REGISTER direction */
    } else {
        *op = substr(line, opFrom, opTo);

        if(*op == NULL) {
            handleError(INVALID_DIRECT_NOTATION, NULL);
        }

        *opType = DIRECT;

        if(!isalpha(**op)) {

            handleError(INVALID_DIRECT_NOTATION, *op);
            return FALSE;
        }

        while(isalnum(*((*op) + ++helperI)));
        if(*((*op) + helperI) != '\0') {

            handleError(INVALID_DIRECT_NOTATION, ((*op) + ++helperI));
            return FALSE;
        }

         /* Reaching here means we have a valid DIRECT direction */
    }


    return TRUE;
}

/* Construct an AsmInstruction which represents an assmebly instruction line. */
static AsmInstruction allocAsmInstructionINST(
        const char* line,
        const unsigned int labelFrom, const unsigned int labelTo,
        const unsigned int cmdFrom, const unsigned int cmdTo,
        const unsigned int srcOPFrom, const unsigned int srcOPTo,
        const unsigned int dstOPFrom, const unsigned int dstOPTo
        ) {
    
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

    if(!parseOperand(line, srcOPFrom, srcOPTo,
            &asmInstruction->instruction->INST.srcOP,
            &asmInstruction->instruction->INST.srcOPType)) {

        freeAsmInstruction(asmInstruction);
        return NULL;
    }

    if(!parseOperand(line, dstOPFrom, dstOPTo,
            &asmInstruction->instruction->INST.dstOP,
            &asmInstruction->instruction->INST.dstOPType)) {

        freeAsmInstruction(asmInstruction);
        return NULL;
    }

    return asmInstruction;
}

/* Construct an AsmInstruction which represents an assmebly declaration line. */
static AsmInstruction allocAsmInstructionDEF(
        const char* line,
        const unsigned int labelFrom, const unsigned int labelTo,
        const unsigned int declFrom, const unsigned int declTo,
        const unsigned int declDataFrom, const unsigned int declDataTo
        ) {
    
    AsmInstruction asmInstruction = (AsmInstruction) malloc(sizeof(struct AsmInstruction));
    if(asmInstruction == NULL) {
        fatalError(MEMORY_ALLOCATION_FAILURE, "Can't allocate memory for AsmInstruction");
    }

    asmInstruction->instruction = malloc(sizeof(union InstructionUnion));
    if(asmInstruction->instruction == NULL) {
        fatalError(MEMORY_ALLOCATION_FAILURE, "Can't allocate memory for InstructionUnion");
    }

    asmInstruction->label = substr(line, labelFrom, labelTo);

    if(strncmp(line+declFrom, STRING_DEC, declTo - declFrom) == 0) { /* Check
                                                                        from the calculated start location
                                                                        of declaration command to the end
                                                                        for a match of required syntax */
        asmInstruction->instructionType = DATA;
        asmInstruction->instruction->DATA.decData = substr(line, declDataFrom, declDataTo);
        asmInstruction->instruction->DATA.dataType = DataType_STRING;
    } else if(strncmp(line+declFrom, DATA_DEC, declTo - declFrom) == 0) {
        asmInstruction->instructionType = DATA;
        asmInstruction->instruction->DATA.decData = substr(line, declDataFrom, declDataTo);
        asmInstruction->instruction->DATA.dataType = DataType_DATA;
    } else if(strncmp(line+declFrom, ENTRY_DEC, declTo - declFrom) == 0) {
        asmInstruction->instructionType = ENTRY;
        asmInstruction->instruction->ENTRY.referenceName = substr(line, declDataFrom, declDataTo);
    } else if(strncmp(line+declFrom, EXTERN_DEC, declTo - declFrom) == 0) {
        asmInstruction->instructionType = EXTERN;
        asmInstruction->instruction->EXTERN.referenceName = substr(line, declDataFrom, declDataTo);
    } else {
        /* TODO: ERROR unknown declaration type */
        return NULL;
    }
    
    return asmInstruction;
}


void freeAsmInstruction(AsmInstruction asmInstruction) {
    /*
     * Free the whole asmInst memory model...
     * this means go into each and every sub struct, sub union,
     * see what was allocated on the heap and kick it from the
     * memory table, otherwise you have memory leaks, which has
     * direct corelation to the final grade.
     */
    if(asmInstruction != NULL) {
        if(asmInstruction->instructionType == INST) {
            if(asmInstruction->instruction->INST.command != NULL)
                free((char*) asmInstruction->instruction->INST.command);
            if(asmInstruction->instruction->INST.srcOP != NULL)
                free(asmInstruction->instruction->INST.srcOP);
            if(asmInstruction->instruction->INST.dstOP != NULL)
                free(asmInstruction->instruction->INST.dstOP);

            
        } else if(asmInstruction->instructionType == DATA) {
            if(asmInstruction->instruction->DATA.decData != NULL)
                free(asmInstruction->instruction->DATA.decData);
        } else if(asmInstruction->instructionType == ENTRY) {
            if(asmInstruction->instruction->ENTRY.referenceName != NULL)
                free(asmInstruction->instruction->ENTRY.referenceName);
        } else if(asmInstruction->instructionType == EXTERN) {
            if(asmInstruction->instruction->EXTERN.referenceName != NULL)
                free(asmInstruction->instruction->EXTERN.referenceName);
        }

        if(asmInstruction->label != NULL)
            free(asmInstruction->label);


        if(asmInstruction->instruction != NULL)
            free(asmInstruction->instruction);

        if(asmInstruction != NULL)
            free(asmInstruction);
    }
}