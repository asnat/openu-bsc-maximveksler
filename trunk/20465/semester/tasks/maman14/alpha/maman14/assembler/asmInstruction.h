/* 
 * File:   InstructionStructure.h
 * Author: hq4ever
 *
 * Created on February 25, 2010, 11:25 PM
 */

#ifndef _INSTRUCTIONSTRUCTURE_H
#define	_INSTRUCTIONSTRUCTURE_H

typedef enum InstructionType { INST=1, DATA, ENTRY, EXTERN } InstructionType;

typedef enum DataType { DataType_STRING=1, DataType_DATA } DataType;
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
        char* decData;
        DataType dataType;
    } DATA;

    struct {
        char* referenceName;
    } ENTRY;

    struct {
        char* referenceName;
    } EXTERN;

} *InstructionUnion;

typedef struct AsmInstruction {
    char* label;

    InstructionType instructionType;
    InstructionUnion instruction;
    
} *AsmInstruction;


#endif	/* _INSTRUCTIONSTRUCTURE_H */

