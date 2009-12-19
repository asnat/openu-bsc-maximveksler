/* 
 * File:   complex.h
 * Author: Maxim Veksler
 *
 * Created on December 4, 2009, 9:49 PM
 */

#ifndef _COMPLEX_H
#define	_COMPLEX_H

#define DEBUG 0
#define TOK_INPUT "\n\t ,"
#define NO_NUMBER_FOUND 50
#define NO_ERROR 0
#define ERROR_DOUBLE_RETURN_VALUE 0.0

typedef struct {
    double real;
    double imaginary;
} Complex;

void read_comp(Complex *p1, double d1, double d2);
void print_comp(Complex *p);
void add_comp(Complex *p1, Complex *p2);
void sub_comp(Complex *p1, Complex *p2);
void mult_comp_real(Complex *p1, double d);
void mult_comp_img(Complex *p1, double d);
void mult_comp_comp(Complex *p1, Complex *p2);
void abs_comp(Complex *p);

#endif	/* _COMPLEX_H */

