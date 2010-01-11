/* 
 * File:   min_call.c
 * Author: Maxim Veksler 303856983
 *
 * Created on January 11, 2010, 7:43 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdarg.h>

#define LIST_TERMINATOR -1


/* 
 * Compare supplied value and if smallers then known smallest set is as new
 * smallest candidate.
 */
void compareAndSet(int *smallestKnownNumber, int candidate) {
    if(*smallestKnownNumber > candidate) {
        *smallestKnownNumber = candidate;
    }
}

/* Test vararg list of arguments searching for the smallest, store it and return.
 *  On next excustion smallest found from previous iteration will be used as
 *  basis for the searching operation.
 *
 * Input values will be valid int numbers (guranteed by forum post).
 */
int min_value(int val1, ...) {
    static int minimumFoundSoFar = INT_MAX;
    va_list ap;
    int candidate;

    /* Initialize the var_args macros subsystem. */
    va_start(ap, val1);

    /* Initialize the loop. */
    candidate = val1;

    /* Iterate over the list of supplied arguments. */
    while(LIST_TERMINATOR != candidate) {
        compareAndSet(&minimumFoundSoFar, candidate);
        /* fetch next argument. */
        candidate = va_arg(ap, int);
    }

    /* Cleanup for va_* macro subsystem. */
    va_end(ap);

    /* return the smallest number found. */
    return minimumFoundSoFar;
}


/*
 * Main function for testing min_value()...
 */
int main(int argc, char** argv) {
    printf("min_value(-1)           minimum is %d\n", min_value(-1));
    printf("min_value(100,12,99,-1) minimum is %d\n", min_value(100,12,99,-1));
    printf("min_value(3,12,15,-1)   minimum is %d\n", min_value(3,12,15,-1));
    printf("min_value(90,80,70,-1)  minimum is %d\n", min_value(90,80,70,-1));
    printf("min_value(-1)           minimum is %d\n", min_value(-1));
    printf("min_value(1,0,1,0,-1)   minimum is %d\n", min_value(1,0,1,0,-1));
    return (EXIT_SUCCESS);
}

