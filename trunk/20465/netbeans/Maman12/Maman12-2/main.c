/* 
 * File:   main.c
 * Author: hq4ever
 *
 * Created on December 4, 2009, 9:39 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "complex.h"
#include "messages.h"

#define TRUE 1
#define TOK_INPUT "\n\t ,"

void halt(char *input) {
    #if DEBUG
        printf("OUTING");
    #endif
        
    exit(EXIT_SUCCESS);
}

conv_t conversion_array[] = {
    {"halt", halt},
    {"print_comp", print_comp},
    {"add_comp", add_comp},
    {"sub_comp", sub_comp},
    {"mult_comp_real", mult_comp_real},
    {"mult_comp_img", mult_comp_img},
    {"mult_comp_comp", mult_comp_comp},
    {"abs_comp", abs_comp},
    {0, 0},
};


/*
 * 
 */
int main(int argc, char** argv) {
    char userInput[1000];
    char *pch;

    conv_t *dynaFuncHandler;
    
    while(TRUE) {
        printf(PLEASE_ENTER_COMMAND);
        fgets(userInput, 1000, stdin);
        pch = strtok(userInput, TOK_INPUT);

        if(pch != NULL) {
            /* Dynamically seek (&find) correct fuction to call */
            for(dynaFuncHandler = conversion_array;  dynaFuncHandler->function_name && strcmp(pch,  dynaFuncHandler->function_name); dynaFuncHandler++);

            /* If we have found a function at this name */
            if(dynaFuncHandler->function_name) {
                pch = strtok(NULL, TOK_INPUT);
                dynaFuncHandler->pt2func(pch);
            } else {
                fprintf(stderr, NOT_VALID_COMMAND);
            }
        } else {
            fprintf(stderr, NO_COMMAND_INPUT);
        }

        printf("\n");
    }

    printf("\n%s", userInput);
    return EXIT_SUCCESS;
}

