#include <stdio.h>
#include <string.h>
#include "errorHandler.h"

#define OBJ_FILE_SUFFIX ".ob"
#define EXT_FILE_SUFFIX ".ext"
#define ENT_FILE_SUFFIX ".ent"
#define OBJ_SUFFIX_SIZE 3
#define OTHER_SUFFIX_SIZE 4

static char* currentObjFile;
static char* currentExtFile;
static char* currentEntFile;

_bool initOutputFiles(char* filePath){
    unsigned i, fileNameSize;

    fileNameSize = strlen(filePath);

    /* init object file path name */
    if (( currentObjFile = (char*) malloc (fileNameSize*sizeof(char)+OBJ_SUFFIX_SIZE)) == NULL)
        fatalError(MEMORY_ALLOCATION_FAILURE, "failed allocate memory for outputs file");
    strcpy(currentObjFile,filePath);
    strcat(currentObjFile,OBJ_FILE_SUFFIX);

    
}