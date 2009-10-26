/* 
 * File:   abc.c
 * Author: Maxim Veksler 303856983
 *
 * Created on October 24, 2009, 2:20 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * This method gets a string of ASCII characters, the method will seek alphabetic
 *  sequences in the string and will substitude them with a collapsed fomrat
 *  for ex. the String "Hi abcde" would become "Hi a-e".
 *
 * The method works on the supplied string.
 */
void collapse(char source[]) {
    /* sequenceCounter is used while to check if we are in a sequence */
    int sequenceCounter = 0;

    /* insertIndex is a pointer to the correct insertion point for the modified 
     * char array */
    int insertIndex = 0;

    char currentChar;
    char nextChar;
    
    int i = 0;
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
            if(sequenceCounter > 1) { /* We found at least 3 characters in the current sequence... */
                insertIndex -= (sequenceCounter - 1); /* We trim 1 from
                 * sequenceCounter here because the first char is already in
                 * correct position: At the start of the sequence. */
                source[insertIndex++] = '-';
                source[insertIndex] = currentChar;
            }

            sequenceCounter = 0;
        }

        /* "Real Developer won't be in a situation that good developer
         * know how to solve." So... incrementing at the end is less
         * sexy then inside the usage of the variables, yet it is by far less
         * error prone and understandble to the petit human mind. */
        insertIndex++;
        i++;
    } while('\0' != currentChar);
}

/* 
 * Maman 11, assignment 2 implementation:
 * Get string, collpase, print collapsed string.
 */
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

void testRun() {
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
    printf("\n");
}



/*
 * Main for Maman 11, task 2 : String collapsing utility.
 */
int main(int argc, char** argv) {
    /* Input buffer, user should input strings shorther then 200 char */
    char str[200];

    /* To test the function is  */
/*  testRun();  */

    scanf("%s", str);

    /* To answer the maman requirments the function is : */
    collapse_print(str);
    printf("\n");

    return (EXIT_SUCCESS);
}

