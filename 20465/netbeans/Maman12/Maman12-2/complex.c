#include <stdlib.h>
#include <stdio.h>
#include "complex.h"

void ppComplex(Complex complex) {
}

void print_comp(char *input) {
    /* Char holds variable name... */
    #if DEBUG
        printf("print_comp %s", input);
    #endif
}

void add_comp(char *input) {
    /* char holds 2 variable names... */
    #if DEBUG
        printf("add_comp %s", input);
    #endif

    
}

void sub_comp(char *input) {
    /* char holds 2 variable names... */
    #if DEBUG
        printf("sub_comp %s", input);
    #endif

}

void mult_comp_real(char *input) {
    /* char holds 1 variable, 1 float*/
    #if DEBUG
        printf("multi_comp_real %s", input);
    #endif
}

void mult_comp_img(char *input) {
    /* char holds 1 variable, 1 float*/
    #if DEBUG
        printf("multi_comp_img %s", input);
    #endif
}

void mult_comp_comp(char *input) {
    /* char holds 2 variable */
    #if DEBUG
        printf("multi_comp_comp %s", input);
    #endif
}

void abs_comp(char *input) {
    /* char holds 1 variable */
    #if DEBUG
        printf("abs_comp %s", input);
    #endif
}
