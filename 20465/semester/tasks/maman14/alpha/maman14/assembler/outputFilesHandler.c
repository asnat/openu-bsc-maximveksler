#include <stdio.h>
#include <string.h>
#include "errorHandler.h"
#include "constants.h"
#include "outpuFilesHandler.h"

#define OBJ_FILE_SUFFIX ".ob"
#define EXT_FILE_SUFFIX ".ext"
#define ENT_FILE_SUFFIX ".ent"
#define OBJ_SUFFIX_SIZE 3
#define OTHER_SUFFIX_SIZE 4

static char* currentObjFile;
static char* currentExtFile;
static char* currentEntFile;


static char* createFilePath(char* filePrefix,char* suffix,unsigned suffixSize, unsigned pathSize){

    char* filePathPointer;

    if ((  filePathPointer = (char*) malloc (pathSize*sizeof(char)+suffixSize)) == NULL)
        fatalError(MEMORY_ALLOCATION_FAILURE, "failed allocate memory for outputs file");
    strcpy(filePathPointer,filePrefix);
    strcat(filePathPointer,suffix);

    return filePathPointer;
}

void initOutputFiles(char* filePath){
    unsigned fileNameSize;

    fileNameSize = strlen(filePath);

    currentObjFile = createFilePath(filePath, OBJ_FILE_SUFFIX, OBJ_SUFFIX_SIZE, fileNameSize);
    currentEntFile = createFilePath(filePath, ENT_FILE_SUFFIX, OTHER_SUFFIX_SIZE, fileNameSize);
    currentExtFile = createFilePath(filePath, EXT_FILE_SUFFIX, OTHER_SUFFIX_SIZE, fileNameSize);
 
}

