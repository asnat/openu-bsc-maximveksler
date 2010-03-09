/* 
 * File:   AsmCommands.h
 * Author: hq4ever
 *
 * Created on February 28, 2010, 10:52 PM
 */

#ifndef _ASMCOMMANDS_H
#define	_ASMCOMMANDS_H

void process(AsmInstruction asmLineInstruction);

typedef struct {
    char *function_name;
    void (*pt2func)(AsmInstruction);
    //char *helpText;
} conv_t;

short int noParm(char*);
short int oneParm(char*);
short int twoParm(char*);

#endif	/* _ASMCOMMANDS_H */

