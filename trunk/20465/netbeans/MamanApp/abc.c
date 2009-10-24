/* 
 * File:   abc.c
 * Author: Maxim Veksler 303856983
 *
 * Created on October 24, 2009, 2:20 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void collapse(char source[]) {
    if(source[0] == '\0')
        return;

    int sequenceCounter = 0;
    int insertIndex = 0;

    int i = 0;

    char currentChar;
    char nextChar;
    
    do {
        currentChar = source[i];
        nextChar = source[i+1];

        /* We always populate first, to avoid going back and doing the correct
         * copying had we discover that no good sequence was found */
        source[insertIndex] = currentChar;
        
        if(currentChar + 1 == nextChar
                && ((currentChar >= 'a' && currentChar < 'z') || (currentChar >= 'A' && currentChar < 'Z'))) {
            sequenceCounter++;
        } else {
            if(sequenceCounter > 1) {
                insertIndex -= (sequenceCounter - 1); /* We trim 1 from
                 * sequenceCounter here because the first char is already in
                 * correct position: At the start of the sequence.
                 */
                source[insertIndex++] = '-';
                source[insertIndex] = currentChar;
            }

            sequenceCounter = 0;
        }

        insertIndex++;
        i++;
    } while(currentChar != '\0');
}

void collapse_print(char source[]) {
    collapse(source);
    printf("%s", source);
}

void test(char tested[], char expectedResult[]) {
    char str[1000];
    strcpy(str, tested);
    collapse(str);

    if(strcmp(str, expectedResult) != 0) {
        printf("\nFAILED for [%s]::: [%s] != [%s]", tested, str, expectedResult);
    } else {
        printf("\nOK     for [%s]::: [%s]", tested, str);
    }
}



int main(int argc, char** argv) {
    
    test("", "");
    test("a", "a");
    test("abd", "abd");
    test("abc", "a-c");
    test(":;<=>?", ":;<=>?");
    test(">?@ABC", ">?@A-C");
    test("XYZ[", "X-Z[");
    test("^_`abc", "^_`a-c");
    test("xyz{", "x-z{");
    test("abcHHHABCDEFiiilmn", "a-cHHHA-Fiiil-n");
    test("dabcemoqmnopqrrtaduvwxaz", "da-cemoqm-rrtadu-xaz");
    
    return (EXIT_SUCCESS);
}

