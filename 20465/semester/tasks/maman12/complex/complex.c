/* 
* File:   complex.c
* Author: Maxim Veksler 303856983
*
* Created on December 3, 2009, 23:28
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "complex.h"
#include "messages.h"



/* Prity Print a complex number
   input: pointer to Complex */
static void __ppComplex(Complex *complex) {
    printf("%.2f + (%.2f)i", complex->real, complex->imaginary);
}

/* ######################################
 * ###### PUBLIC METHODS ################
 * ######################################
 */
void read_comp(Complex *p1, double d1, double d2) {
    if(p1 != NULL) {
         p1->real = d1;
         p1->imaginary = d2;
    }
}

void print_comp(Complex *p) {
    if(p != NULL) {
        __ppComplex(p);
    }
}

void add_comp(Complex *p1, Complex *p2) {
    Complex *result;

    if(p1 != NULL) {
        if(p2 != NULL) {
            result = (Complex*) malloc(sizeof(Complex));

            if(result == NULL) {
                fprintf(stderr, NO_FREE_MEMORY);
                return;
            }

            result->real = p1->real + p2->real;
            result->imaginary = p1->imaginary + p2->imaginary;

            __ppComplex(result);
            free(result);
        } /*if(p2 != NULL)*/
    } /*if(p1 != NULL)*/
} /*add_comp*/

void sub_comp(Complex *p1, Complex *p2) {
    Complex *result;

    if(p1 != NULL) {
        if(p2 != NULL) {
            result = (Complex*) malloc(sizeof(Complex));

            if(result == NULL) {
                fprintf(stderr, NO_FREE_MEMORY);
                return;
            }

            result->real = p1->real - p2->real;
            result->imaginary = p1->imaginary - p2->imaginary;

            __ppComplex(result);
            free(result);
        }
    }
}

void mult_comp_real(Complex *p1, double d) {
    Complex *result;
    
    if(p1 != NULL) {
        result = (Complex*) malloc(sizeof(Complex));

        if(result == NULL) {
            fprintf(stderr, NO_FREE_MEMORY);
            return;
        }

        result->real = p1->real * d;
        result->imaginary = p1->imaginary * d;

        __ppComplex(result);
        free(result);
    }
}

void mult_comp_img(Complex *p1, double d) {
    Complex *result;

    if(p1 != NULL) {
        result = (Complex*) malloc(sizeof(Complex));

        if(result == NULL) {
            fprintf(stderr, NO_FREE_MEMORY);
            return;
        }

        result->real = -1 * p1->imaginary * d;
        result->imaginary = p1->real * d;

        __ppComplex(result);
        free(result);
    }
}

void mult_comp_comp(Complex *p1, Complex *p2) {
    Complex *result;

    if(p1 != NULL && p2 != NULL) {
       result = (Complex*) malloc(sizeof(Complex));

        if(result == NULL) {
            fprintf(stderr, NO_FREE_MEMORY);
            return;
        }

        result->real = (p1->real * p2->real - p1->imaginary * p2->imaginary);
        result->imaginary = (p1->real * p2->imaginary + p1->imaginary * p2->real);

        __ppComplex(result);
        free(result);
    }
}

void abs_comp(Complex *p) {
    double complexAbsValue;
    
    if(p != NULL) {
        complexAbsValue = sqrt((p->real * p->real) + (p->imaginary * p->imaginary));
        printf("|");
        __ppComplex(p);
        printf("|=%.2f", complexAbsValue);
    }
}
