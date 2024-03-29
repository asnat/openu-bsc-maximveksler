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

#define PERMITTED_LINE_LENGTH 81 /* 81 because we have 80 valid chars +1 for \0 */

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
    int index = 0;

    int labelFrom = 0;
    int labelTo = 0;

    int cmdFrom = 0;
    int cmdTo = 0;

    int srcOPFrom = 0;
    int srcOPTo = 0;

    int dstOPFrom = 0;
    int dstOPTo = 0;

    int declFrom = 0;
    int declTo = 0;

    int declDataFrom = 0;
    int declDataTo = 0;

    
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

                if(labelTo - labelFrom > 30) {
                    handleError(LABEL_TOO_LONG, NULL);
                    return NULL;
                }
                
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
    }
    if(line[index] == '\0')
        return NULL; /* It was a line full of white space */

    if(strlen(line) >= PERMITTED_LINE_LENGTH) {
        handleError(ASSEMBLY_LINE_TOO_LONG, NULL);
        return NULL;
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

        /* Go back to avoid space... */
        index = index-1;
        if(index > 0 && isspace(line[index])) {
            while(index > 0 && isspace(line[--index]));
        }
        index = index + 1;

        declDataTo = index;

        return allocAsmInstructionDEF(line, labelFrom, labelTo, declFrom, declTo, declDataFrom, declDataTo);
    } else if (isalpha(line[index])) {
        /* Command */
        cmdFrom = index;

        while(isalpha(line[++index])); /* Consume cmd chars */
        cmdTo = index;
        
        if(line[index] == '\0') { /* Command has not operands */
            return allocAsmInstructionINST(line, labelFrom, labelTo, cmdFrom, cmdTo, 0, 0, 0, 0);
        } else if(!isspace(line[index])) {
            /* after command we require white space seperator */
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

        if(line[index] == '\0') { /* Command has just 1 operand, pass src operand as dst operand */
            return allocAsmInstructionINST(line, labelFrom, labelTo, cmdFrom, cmdTo, 0, 0, srcOPFrom, srcOPTo);
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

        /* Command has 2 operands */
        return allocAsmInstructionINST(line, labelFrom, labelTo, cmdFrom, cmdTo, srcOPFrom, srcOPTo, dstOPFrom, dstOPTo);
    } else {

        handleError(INVALID_ASSEMBLY_SYNTAX, NULL);
        return NULL;
    }


    return NULL; /* We should never reach here */
}

/* Parse operand string into API readable format, on failure method will
 * return FALSE */
static _bool parseOperand(const char* line, unsigned int opFrom, unsigned int opTo,
        char **op, AddressingType* opType) {

    unsigned int helperI = 0;

    if(line[opFrom] == '#') { /* Number, not label, takes direct value */
        /* Numbers start from second character until the end of the operand */
        *op = substr(line, opFrom+1, opTo);

        /* Empty number string is an error */
        if(*op == NULL) {
            handleError(OPERAND_IS_NOT_VALID_NUMBER, NULL);
        }
        
        *opType = IMMIDIATE;

        /* First char of number must be either +, - or digit */
        if(**op != '+' && **op != '-' && !isdigit(**op)) {

            handleError(OPERAND_IS_NOT_VALID_NUMBER, *op);
            return FALSE;
        }

        helperI = 0;
        /* Verify that from second to end all digits are numbers */
        while(isdigit(*((*op) + ++helperI)));

        if(*((*op) + helperI) != '\0') {
            
            handleError(OPERAND_IS_NOT_VALID_NUMBER, (*op) + helperI);
            return FALSE;
        }
        /* Reaching here means we have a valid IMMIDIATE direction */
    } else if (line[opFrom] == '@') { /* Indirect references start with @ */
        /* Actual label code starts from second char until end of string */
        *op = substr(line, opFrom+1, opTo);

        /* Empty operand label name is an error */
        if(*op == NULL) {
            handleError(INVALID_INDIRECT_NOTATION, NULL);
            return FALSE;
        }

        *opType = INDIRECT;

        /* First label char must be alpha */
        if(!isalpha(**op)) {

            handleError(INVALID_INDIRECT_NOTATION, *op);
            return FALSE;
        }

        /* From second to last char valid chars are either alpha or numeric */
        while(isalnum(*((*op) + ++helperI)));
        if(*((*op) + helperI) != '\0') {

            handleError(INVALID_INDIRECT_NOTATION, ((*op) + ++helperI));
            return FALSE;
        }
        /* Reaching here means we have a valid INDIRECT direction */  
    } else if (line[opFrom] == 'r' && (opTo - opFrom) == 2) { /* Register is length 2 and starts with small "r" */
        *op = substr(line, opFrom, opTo);

        /* Empty operand is an error, should not happen in this case */
        if(*op == NULL) {
            handleError(INVALID_REGISTER_NOTATION, NULL);
            return FALSE;
        }

        *opType = REGISTER;

        /* Valid register syntax contains proper range for second char */
        if(*((*op) + 1) > '7' || *((*op) + 1) < '0') {

            handleError(INVALID_REGISTER_NOTATION, *op);
            return FALSE;
        }

         /* Reaching here means we have a valid REGISTER direction */
    } else {
        /* Reaching here means we probably have a plain label */
        *op = substr(line, opFrom, opTo);

        /* Operand should not be null */
        if(*op == NULL) {
            handleError(INVALID_DIRECT_NOTATION, NULL);
            return FALSE;
        }

        *opType = DIRECT;

        /* Label contains alpha for first character */
        if(!isalpha(**op)) {

            handleError(INVALID_DIRECT_NOTATION, *op);
            return FALSE;
        }

        /* Label contains alnum from second char to end of line */
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

    if(srcOPTo - srcOPFrom > 0) {
        if(!parseOperand(line, srcOPFrom, srcOPTo,
                &asmInstruction->instruction->INST.srcOP,
                &asmInstruction->instruction->INST.srcOPType)) {

            freeAsmInstruction(asmInstruction);
            return NULL;
        }
    } else {
        asmInstruction->instruction->INST.srcOP = NULL;
        asmInstruction->instruction->INST.srcOPType = NO_OP;
    }

    if(dstOPTo - dstOPFrom > 0) {
        if(!parseOperand(line, dstOPFrom, dstOPTo,
                &asmInstruction->instruction->INST.dstOP,
                &asmInstruction->instruction->INST.dstOPType)) {

            freeAsmInstruction(asmInstruction);
            return NULL;
        }
    } else {
        asmInstruction->instruction->INST.dstOP = NULL;
        asmInstruction->instruction->INST.dstOPType = NO_OP;
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