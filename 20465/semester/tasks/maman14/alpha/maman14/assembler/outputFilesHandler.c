#include <stdio.h>
#include <string.h>
#include "errorHandler.h"
#include "constants.h"
#include "outpuFilesHandler.h"
#include "codeSegmentMgr.h"
/* #include dataSegmentMgr.h */

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

_bool writeToOutputFile(char* fileType, char* labelName, unsigned address){
    FILE* fileName;
    
    switch (fileType){
        case EXT_FILE:
            if ((fileName = fopen(currentExtFile,"w+")) != NULL)
                fprintf(currentExtFile,"%s\t0%u", labelName, address);
            else {
                perror(currentExtFile);
                return FALSE;
            }
            break;
        case ENT_FILE:
            if ((fileName = fopen(currentEntFile,"w+")) != NULL)
                fprintf(currentEntFile,"%s\t0%u", labelName, address);
            else {
                perror(currentEntFile);
                return FALSE;
            }
            break;
        default:
            return FALSE;
    }
    if (fileType == EXT_FILE)
        fclose(currentExtFile);
    else
        fclose(currentEntFile);
    return TRUE;
}

 _bool writeObjectFileFirstRow(){
     FILE* obFile;

     if ((obFile = fopen(currentObjFile,"w")) == NULL){
         perror(currentObjFile);
         return FALSE;
     }
     fprintf(currentObjFile,"\t\t0%u 0%u",getIC,getID);
     fclose(currentObjFile);
     return TRUE;
 }


_bool writeToObjFile(unsigned address, unsigned short data, char linkerData){
    fprintf
}


void initOutputFiles(char* filePath){
    unsigned fileNameSize;

    fileNameSize = strlen(filePath);

    currentObjFile = createFilePath(filePath, OBJ_FILE_SUFFIX, OBJ_SUFFIX_SIZE, fileNameSize);
    currentEntFile = createFilePath(filePath, ENT_FILE_SUFFIX, OTHER_SUFFIX_SIZE, fileNameSize);
    currentExtFile = createFilePath(filePath, EXT_FILE_SUFFIX, OTHER_SUFFIX_SIZE, fileNameSize);
 
}

