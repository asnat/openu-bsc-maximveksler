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
    FILE* fh;
    
    switch (fileType){
        case EXT_FILE:
            if ((fh = fopen(currentExtFile,"w+")) != NULL)
                if ((fprintf(fh,"%s\t0%u", labelName, address)) < 0){
                    handleError(CANT_WRITE_TO_EXT_FILE, currentExtFile);
                    fclose(currentExtFile);
                    return FALSE;
                }
            else {
                perror(currentExtFile);
                return FALSE;
            }
            break;
        case ENT_FILE:
            if ((fh = fopen(currentEntFile,"w+")) != NULL)
                if((fprintf(fh,"%s\t0%u", labelName, address)) < 0 ){
                    handleError(CANT_WRITE_TO_ENT_FILE, currentEntFile);
                    fclopse(fh);
                    return FALSE;
                }
            else {
                perror(currentEntFile);
                return FALSE;
            }
            break;
        default:
            return FALSE;
    }
    if (fileType == EXT_FILE)
        fclose(fh);
    else
        fclose(fh);
    return TRUE;
}


 _bool writeObjectFileFirstRow(){
     FILE* obFile;

     if ((obFile = fopen(currentObjFile,"w")) == NULL){
         perror(currentObjFile);
         return FALSE;
     }
     fprintf(obFile,"\t\t0%u 0%u",getIC,getID);
     fclose(currentObjFile);
     return TRUE;
 }



_bool writeToObjFile(unsigned address, unsigned short data, char linkerData){
    FILE* obfile;

    if ((obfile = fopen(currentObjFile,"w+")) == NULL){
        handleError(CANT_OPEN_OBJECT_FILE, currentObjFile);
        return FALSE;
    }
    if((fprintf(obfile,"0%2ou 0%2ohu %2c", address, data, linkerData)) < 0){
        handleError(CANT_WRITE_TO_OBJ_FILE, currentObjFile);
        fclose(obfile);
        return FALSE;
    }
    fclose(obfile);
    return TRUE;
}


void initOutputFiles(char* filePath){
    unsigned fileNameSize;

    fileNameSize = strlen(filePath);

    currentObjFile = createFilePath(filePath, OBJ_FILE_SUFFIX, OBJ_SUFFIX_SIZE, fileNameSize);
    currentEntFile = createFilePath(filePath, ENT_FILE_SUFFIX, OTHER_SUFFIX_SIZE, fileNameSize);
    currentExtFile = createFilePath(filePath, EXT_FILE_SUFFIX, OTHER_SUFFIX_SIZE, fileNameSize);
 
}

