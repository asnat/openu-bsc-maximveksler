/* 
 * File:   doll.c
 * Author: Maxim Veksler
 *
 * Created on October 24, 2009, 1:05 PM
 */

#include <stdio.h>
#include <stdlib.h>

/* Error codes: */
#define DOLL_NO_EXCHANGE_RATE -1
#define DOLL_SUCCESS 0

void printExchange(float rate, float value) {
    printf("%-40f%-40f\n", value, value * rate);
}

/*
 * Get exchange rate, then read values until EOF printing converted values
 * by given rate. At the end print summary of all inputed values and their
 * convertion.
 */
int forexCalc() {
    float exchangeRate;
    float totalUS = 0;

    if(scanf("%f", &exchangeRate) != 1) {
        return DOLL_NO_EXCHANGE_RATE;
    }

    printf("%-40s%-40s\n", "$", "IS");

    float currentValue;
    while(scanf("%f", &currentValue) != EOF) {
        totalUS += currentValue;
        printExchange(exchangeRate, currentValue);
    }

    printExchange(exchangeRate, totalUS);
    
    return DOLL_SUCCESS;
}

/*
 * Main for Maman 11, task 1 : Exchange Rate calculator
 */
int ___doll_loc_main(int argc, char** argv) {
    int ret = forexCalc();

    switch (ret) {
        case DOLL_NO_EXCHANGE_RATE:
            printf("No exchange rate was supplied\n");
            break;
    }

    /* If forexCalc returned success the application was succesful, in all
     * other cases we failed. */
    return ((ret == DOLL_SUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE);
}

