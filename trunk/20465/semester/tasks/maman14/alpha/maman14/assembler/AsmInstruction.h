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
typedef enum AddressingType { IMMIDIATE=0, DIRECT=1, INDIRECT=3, REGISTER=4 } AddressingType;

typedef union InstructionUnion {
    struct {
        // Normal instructions (instructionType=INST)
        char* command;
        char* operand1;
        AddressingType operand1Type;
        char* operand2;
        AddressingType operand2Type;
    } INST;

    struct {
        // Normal instructions (instructionType=DATA)
        char* label;
        char* command;
        char* operand1;
        char* operand2;
    } DATA;   
} *InstructionUnion;


typedef struct AsmInstruction {
    char* label;
    int lineNumber;
    
    InstructionType instructionType;
    InstructionUnion instruction;
    
} *AsmInstruction;


#endif	/* _INSTRUCTIONSTRUCTURE_H */

