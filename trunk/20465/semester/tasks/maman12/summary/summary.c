/* 
 * File:   summary.c
 * Author: Maxim Veksler
 *
 * Created on December 4, 2009, 3:09 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "manipulation.h"

/*
 * Main for Maman 12, task 1 : Array summary utility
 */
int main(int argc, char** argv) {
    int resultsSize;
    int* results;
    int* aggregated;

    /* Parse the string input, convert it into int[] */
    printf("Please enter number to calculate series from them: ");
    results = parseInput(&resultsSize);

    if(resultsSize == 0) {
        return EXIT_FAILURE; /*We want results for input, otherwise we exit*/
    }

    /* Process the input further to allow task logic */
    aggregated = aggregateArray(results, resultsSize);

    
    /* Finally print the result */
    printf("\n");
    int i = 0;
    while(i < resultsSize) {
        printf("%d ", *(aggregated+i));
        i++;
    }
    printf("\n");
    
    /* Be free my memory, FLY like the wind!! */
    free(aggregated);
    free(results);
    
    return EXIT_SUCCESS;
}
