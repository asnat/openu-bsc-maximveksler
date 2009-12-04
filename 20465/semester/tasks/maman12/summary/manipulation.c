/*
 * File:   manipulation.c
 * Author: Maxim Veksler
 *
 * Created on December 4, 2009, 3:09 AM
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static char PARSER_PATTERN[]  = "\t ";
/*
 * Parse the input from user, dynamically allocate memory to the maximum
 * possible requirment. Then convert the array of string tokens into an
 * simple array of integers.
 */
int* parseInput(char* input, int* nOfResults) {
    

    /* Allocate memory by the maximum possibly required size for int... */
    int *results = (int*) malloc(strlen(input) * sizeof(int));

    int* insertIterator = results;
    char* pch;

    
    /* We trash the user input, but it's cool - Worthless as usual. */
    pch = strtok(input, "\t ");
    *nOfResults = 0;
    
    while(pch != NULL) {
        (*nOfResults)++;
        
        *insertIterator = atoi(pch);
        insertIterator++;
        pch = strtok(NULL, "\t ");
    }

    return results;
}


/*
 * Summary the values given in the int array and return adress to new array
 * containing an increasin sum of the values.
 */
int* aggregateArray(int* inputArray, int size) {
    int* results;

    /* Allocate memory the same size as input array */
    results = malloc(sizeof(int) * size);

    int sum = 0;

    int i = 0;
    while(i < size) {
        sum += *(inputArray+i);
        *(results+i) = sum;
        i++;
    }
    
    return results;
}
