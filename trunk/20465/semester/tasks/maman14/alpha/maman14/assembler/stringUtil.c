#include <string.h>
#include <stdlib.h>
#include "errorHandler.h"

char* substr(const char* source, const unsigned int lineNumber, const unsigned int fromPos, const unsigned int toPos) {
    char* newStr;
    unsigned int i;
    unsigned int n = toPos-fromPos;

    newStr = (char*) malloc(n+1);
    if(newStr == NULL) {
        fatalError(lineNumber, MEMORY_ALLOCATION_FAILURE, "Can't allocate memory for String", source);
    }

    for(i = 0; i <= n; i++) {
        newStr[i] = source[fromPos+i];
    }

    newStr[n+1] = '\0';

    return newStr;
}

