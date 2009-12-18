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
#include "maindefs.h"


static void halt() {
    /* Easter egg code... */
    char *pch;
    int jokeIndex = 0;
    char *jokes[] = { "What?!?!? !!!", 
		      "WHAT DO YOU WANT FROM ME???",
		      "Ya neit speak your language",
                      "What do you think I am? a Telepathic vending machine?",
		      "Stop it!",
                      "Go away!",
                      "Leave me alone.",
                      "Dude, I mean it!!",
                      "That's it, You have been telekanisized!!  ( http://www.tapuz.co.il/blog/userBlog.asp?FolderName=orenzarif )"
                   };
    for(pch = strtok(NULL, TOK_INPUT), jokeIndex = 0; pch != NULL && jokeIndex < 9; pch = strtok(NULL, TOK_INPUT), jokeIndex++) {
       printf("\"%s\" Ha? -- %s\n", pch, jokes[jokeIndex]);
    }
    /* Easter egg code ends here... */

    exit(EXIT_SUCCESS);
}

Complex A;
Complex B;
Complex C;
Complex D;
Complex E;
Complex F;

static int errno;

/* extract from the input the next complex number to be used by string matching
 *  input: The input string that was types by the user
 *  output: pointer to the complex variable to be used, if not found then NULL */
static Complex* __getComplex(char *input) {
    char *pch;

    pch = strtok(input, TOK_INPUT);

    if(pch == NULL || strlen(pch) != 1 || !(pch[0] >= 'A' && pch[0] <= 'F')) {
        fprintf(stderr, INVALID_VARIABLE_NAME);
        return NULL;
    } else {
        switch (pch[0]) {
            case 'A' : return &A;
            case 'B' : return &B;
            case 'C' : return &C;
            case 'D' : return &D;
            case 'E' : return &E;
            case 'F' : return &F;
        }
    }

    return NULL;
}


/* extract from the input a double number as was typed by the user
 *  input: The input string that was types by the user
 *  output: double if not found then 0.0 and errno is set to NO_NUMBER_FOUND */
static double __getDouble(char *input, char* info_TargetParameterName) {
    char *pch;

    errno = NO_ERROR;

    pch = strtok(input, TOK_INPUT);

    if(pch == NULL) {
        errno = NO_NUMBER_FOUND;
        fprintf(stderr, "%s %s %s", WRONG_PARAMETERS, info_TargetParameterName, NO_DOUBLE_VALUE_FOUND);
        return ERROR_DOUBLE_RETURN_VALUE;
    } else {
        /* The next block verifies we are dealing with valid floating point
         * number representation, note we do not support scientific E notation...
         */
        char *c = pch;
        char testedChar;

        testedChar = *c;
        if(testedChar == '+' || testedChar == '-') {
            c++;
            testedChar = *c;
        }

        while((testedChar >= '0' && testedChar <= '9')) {
            testedChar = *(++c);
        }

        if(testedChar != '.') {
            if(testedChar != '\0') {
                errno = NO_NUMBER_FOUND;
                fprintf(stderr, "%s %s %s", WRONG_PARAMETERS, info_TargetParameterName, NO_DOUBLE_VALUE_FOUND);
                return ERROR_DOUBLE_RETURN_VALUE;
            }
        } else {
            testedChar = *(++c);
        }

        while((testedChar >= '0' && testedChar <= '9')) {
            testedChar = *(++c);
        }

        if(testedChar != '\0') {
            errno = NO_NUMBER_FOUND;
            fprintf(stderr, "%s %s %s", WRONG_PARAMETERS, info_TargetParameterName, NO_DOUBLE_VALUE_FOUND);
            return ERROR_DOUBLE_RETURN_VALUE;
        }
    }

    return atof(pch);

}

static void read_comp_integration(char* input) {
    Complex *p1;
    double d1;
    double d2;

    /* char holds 1 variable name, 2 float... */
    #if DEBUG
        printf("add_comp %s\n", input);
    #endif

    p1 = __getComplex(input);
    if(p1 != NULL) {
         d1 = __getDouble(NULL, "second");
         if(errno == NO_NUMBER_FOUND) {
             return;
         }

         d2 = __getDouble(NULL, "third");
         if(errno == NO_NUMBER_FOUND) {
             return;
         }

         read_comp(p1, d1, d2);
    }
}

static void print_comp_integration(char *input) {
    Complex *p;

    /* Char holds variable name... */
    #if DEBUG
        printf("print_comp_integration %s\n", input);
    #endif

    p = __getComplex(input);

    if(p != NULL) {
        print_comp(p);
    }
}

static void add_comp_integration(char *input) {
    Complex *p1;
    Complex *p2;

    /* char holds 2 variable names... */
    #if DEBUG
        printf("add_comp %s\n", input);
    #endif

    p1 = __getComplex(input);
    if(p1 != NULL) {
        p2 = __getComplex(NULL);

        if(p2 != NULL) {
            add_comp(p1, p2);
        } /*if(p2 != NULL)*/
    } /*if(p1 != NULL)*/
} /*add_comp*/

static void sub_comp_integration(char *input) {
    Complex *p1;
    Complex *p2;

    /* char holds 2 variable names... */
    #if DEBUG
        printf("sub_comp %s\n", input);
    #endif

    p1 = __getComplex(input);
    if(p1 != NULL) {
        p2 = __getComplex(NULL);

        if(p2 != NULL) {
            sub_comp(p1, p2);
        }
    }
}

static void mult_comp_real_integration(char *input) {
    Complex *p1;
    double d;

    /* char holds 1 variable, 1 float*/
    #if DEBUG
        printf("multi_comp_real %s\n", input);
    #endif


    p1 = __getComplex(input);
    if(p1 != NULL) {
         d = __getDouble(NULL, "second");
         if(errno == NO_NUMBER_FOUND) {
             return;
         }
    }

    mult_comp_real(p1, d);
}

static void mult_comp_img_integration(char *input) {
    Complex *p1;
    double d;

    /* char holds 1 variable, 1 float imaginary*/
    #if DEBUG
        printf("multi_comp_img %s\n", input);
    #endif


    p1 = __getComplex(input);
    if(p1 != NULL) {
         d = __getDouble(NULL, "second");
         if(errno == NO_NUMBER_FOUND) {
             return;
         }
    }

    mult_comp_img(p1, d);
}

static void mult_comp_comp_integration(char *input) {
    Complex *p1;
    Complex *p2;

    /* char holds 2 variable */
    #if DEBUG
        printf("multi_comp_comp %s\n", input);
    #endif

    p1 = __getComplex(input);
    if(p1 != NULL) {
        p2 = __getComplex(NULL);

        if(p2 != NULL) {
            mult_comp_comp(p1, p2);
        }
    }
}

static void abs_comp_integration(char *input) {
    Complex *p;

    /* char holds 1 variable */
    #if DEBUG
        printf("abs_comp %s\n", input);
    #endif

    p = __getComplex(input);

    if(p != NULL) {
        abs_comp(p);
    }

}

static conv_t conversion_array[] = {
    {"read_comp", read_comp_integration},
    {"print_comp", print_comp_integration},
    {"add_comp", add_comp_integration},
    {"sub_comp", sub_comp_integration},
    {"mult_comp_real", mult_comp_real_integration},
    {"mult_comp_img", mult_comp_img_integration},
    {"mult_comp_comp", mult_comp_comp_integration},
    {"abs_comp", abs_comp_integration},
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
            /* Check if it's time to die */
            if(strncmp(HALT_FUNCTION_NAME, pch, 4 /*ester egg*/) == 0) {
                halt();
            }

            /* Dynamically seek (&find) correct fuction to call
             * We stop either on dynaFuncHandler->function_name == NULL
             * or on match strcmp(pch,  dynaFuncHandler->function_name) == 0
             */
            for(dynaFuncHandler = conversion_array;  dynaFuncHandler->function_name && strcmp(pch,  dynaFuncHandler->function_name); dynaFuncHandler++);

            /* If we have found a function at this name */
            if(dynaFuncHandler->function_name) {
                /* We want to pass the next location after the function name in the general user input string */
                dynaFuncHandler->pt2func(&userInput[strlen(pch)+1]);
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

