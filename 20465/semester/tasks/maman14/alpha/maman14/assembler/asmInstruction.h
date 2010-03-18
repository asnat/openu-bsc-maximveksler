/* 
 * File:   InstructionStructure.h
 * Author: hq4ever
 *
 * Created on February 25, 2010, 11:25 PM
 */

#ifndef _INSTRUCTIONSTRUCTURE_H
#define	_INSTRUCTIONSTRUCTURE_H

typedef enum InstructionType { INST, DATA, ENTRY, EXTERN } InstructionType;

typedef enum DataType { DataType_STRING, DataType_DATA } DataType;
typedef enum AddressingType { IMMIDIATE=1, DIRECT=2, INDIRECT=4, REGISTER=8, NO_OP=16 } AddressingType;

typedef union InstructionUnion {
    struct {
        /* Normal instructions (instructionType=INST) */
        const char* command;
        char* srcOP;
        AddressingType srcOPType;
        char* dstOP;
        AddressingType dstOPType;
    } INST;

    struct {
        /* Normal instructions (instructionType=DATA) */
        char* command;
        char* operand1;
        char* operand2;
    } DATA;   
} *InstructionUnion;

typedef struct AsmInstruction {
    /* Used for logging purpuses only... In order to easly print to stderr the
     * offending line.
     */
    const char* _log_unparsedAssemblyLine;
    
    char* label;
    unsigned lineNumber;
    
    InstructionType instructionType;
    InstructionUnion instruction;
    
} *AsmInstruction;


#endif	/* _INSTRUCTIONSTRUCTURE_H */

