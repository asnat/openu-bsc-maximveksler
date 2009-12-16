#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "complex.h"
#include "messages.h"

Complex A;
Complex B;
Complex C;
Complex D;
Complex E;
Complex F;

static Complex* __getComplexAddress(char *input) {
    char *pch;

    if(input == NULL) {
        fprintf(stderr, INVALID_VARIABLE_NAME);
        return NULL;
    }

    pch = strtok(input, TOK_INPUT);

    if(strlen(pch) != 1 || (pch[0] - 'A' < 0) || (pch[0] - 'A' > 5)) {
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
}

static void __ppComplex(Complex *complex) {
    printf("%c = %.2f + (%.2f)i", complex->registerId, complex->real, complex->imaginary);
}

void initializeRegisters() {
    A.registerId = 'A';
    B.registerId = 'B';
    C.registerId = 'C';
    D.registerId = 'D';
    E.registerId = 'E';
    F.registerId = 'F';
}

void print_comp(char *input) {
    /* Char holds variable name... */
    #if DEBUG
        printf("print_comp %s\n", input);
    #endif

    Complex *p = __getComplexAddress(input);

    if(p != NULL) {
        __ppComplex(p);
    }
}

void add_comp(char *input) {
    /* char holds 2 variable names... */
    #if DEBUG
        printf("add_comp %s\n", input);
    #endif

    
}

void sub_comp(char *input) {
    /* char holds 2 variable names... */
    #if DEBUG
        printf("sub_comp %s\n", input);
    #endif

}

void mult_comp_real(char *input) {
    /* char holds 1 variable, 1 float*/
    #if DEBUG
        printf("multi_comp_real %s\n", input);
    #endif
}

void mult_comp_img(char *input) {
    /* char holds 1 variable, 1 float*/
    #if DEBUG
        printf("multi_comp_img %s\n", input);
    #endif
}

void mult_comp_comp(char *input) {
    /* char holds 2 variable */
    #if DEBUG
        printf("multi_comp_comp %s\n", input);
    #endif
}

void abs_comp(char *input) {
    /* char holds 1 variable */
    #if DEBUG
        printf("abs_comp %s\n", input);
    #endif
}
