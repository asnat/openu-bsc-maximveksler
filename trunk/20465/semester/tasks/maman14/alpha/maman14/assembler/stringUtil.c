#include <string.h>
#include <stdlib.h>
#include "errorHandler.h"

char* substr(const char* source, const unsigned int fromPos, const unsigned int toPos) {
    char* newStr;
    unsigned int i;
    unsigned int n = toPos-fromPos;

    if(n <= 0) /* we do no copying when range is invalid, this is not an error */
        return NULL;

    newStr = (char*) malloc(n+1);
    if(newStr == NULL) {
        fatalError(MEMORY_ALLOCATION_FAILURE, "Can't allocate memory for String");
    }

    for(i = 0; i < n; i++) {
        newStr[i] = source[fromPos+i];
    }

    newStr[n] = '\0';

    return newStr;
}

