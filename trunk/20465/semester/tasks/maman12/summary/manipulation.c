/*
 * File:   manipulation.c
 * Author: Maxim Veksler
 *
 * Created on December 4, 2009, 3:09 AM
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
 * Parse the input from user, dynamically allocate memory to the maximum
 * possible requirment. Then convert the array of string tokens into an
 * simple array of integers.
 */
int* parseInput(int* nOfResults) {
    int *results = malloc(sizeof(int));
    int result_size = 1;
 
    int currentValue;
 
    /* We assume here that the input coming from the user is valid... */
    while(scanf("%d", &currentValue) != EOF) {
       int *p = realloc(results, (result_size + 1) * sizeof(int));
       if(!p) {
          free(results);
          return NULL; /* BIG PROBLEM - NO MEMORY !! */
       }
       results = p;
       results[result_size - 1] = currentValue;
       result_size++;
    }

    *nOfResults = result_size-1;
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
