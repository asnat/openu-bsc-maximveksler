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

typedef struct AsmInstruction {
    // Some kind of bit field that says Entety, instruction, or Data
    InstructionType instructionType;  // INST, DATA, ENTRY, EXTERN

    // Normal instructions (instructionType=INST)
    char* label;
    char* command;
    char* operand1;
    char* operand2;

    // Entety instruction (instructionType=ENTRY)
    
    // command contains all the data that we need, pointing at the label
    // that should be externilized.

    // Entety instruction (instructionType=DATA)
    // label holds the label (if such exists) for this data
    DataType dataType; // STRING, DATA
    void* pointerToData;

} *AsmInstruction;
#endif	/* _INSTRUCTIONSTRUCTURE_H */

