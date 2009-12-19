/* 
 * File:   maindefs.h
 * Author: Maxim Veksler 303856983
 *
 * Created on December 16, 2009, 7:42 PM
 */

#ifndef _MAINDEFS_H
    #define	_MAINDEFS_H

    #define USER_INPUT_SIZE 100
    #define TRUE 1
    #define HALT_FUNCTION_NAME "halt"
    #define HELP_FUNCTION_NAME "help"

typedef struct {
    char *function_name;
    void (*pt2func)(char*);
    char *helpText;
} conv_t;

#endif	/* _MAINDEFS_H */

