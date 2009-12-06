/* 
 * File:   complex.h
 * Author: hq4ever
 *
 * Created on December 4, 2009, 9:49 PM
 */

#ifndef _COMPLEX_H
#define	_COMPLEX_H

#define DEBUG 1

typedef struct {
    int real;
    int imaginary;
} Complex;

typedef struct {
    char *function_name;
    void (*pt2func)(char*);
} conv_t;


void ppComplex(Complex);
void print_comp(char*);
void add_comp(char*);
void sub_comp(char*);
void mult_comp_real(char*);
void mult_comp_img(char*);
void mult_comp_comp(char*);
void abs_comp(char*);

#endif	/* _COMPLEX_H */

