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

    /* Read input from user */
    char str[1000];
    scanf("%s", str);
    printf("%s", str);
    
    /* Parse the string input, convert it into int[] */
    results = parseInput(str, &resultsSize);

    /* Process the input further to allow task logic */
    aggregated = aggregateArray(results, resultsSize);

    /* Finally print the result */
    int i = 0;
    while(i < resultsSize) {
        printf("%d\n", *(aggregated+i));
        i++;
    }

    
    /* Be free my memory, FLY like the wind!! */
    free(aggregated);
    free(results);
    
    return EXIT_SUCCESS;
}