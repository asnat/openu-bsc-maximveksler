#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "errorHandler.h"
#include "constants.h"
#include "outputFilesHandler.h"
#include "codeSegmentMgr.h"
#include "dataSegmentMgr.h"

#define OBJ_FILE_SUFFIX ".ob"
#define EXT_FILE_SUFFIX ".ext"
#define ENT_FILE_SUFFIX ".ent"
#define OBJ_SUFFIX_SIZE 3
#define OTHER_SUFFIX_SIZE 4

static char* currentObjFile;
static char* currentExtFile;
static char* currentEntFile;


static char* createFilePath(char* filePrefix, const char* suffix){

    char* filePathPointer;

    filePathPointer = malloc(strlen(filePrefix) * sizeof(char) + strlen(suffix) * sizeof(char) + 1);
/*
    if ((  filePathPointer = (char*) malloc (pathSize*sizeof(char)+suffixSize)+1000) == NULL)
        fatalError(MEMORY_ALLOCATION_FAILURE, "failed allocate memory for outputs file");
 */

    strcpy(filePathPointer,filePrefix);
    strcat(filePathPointer,suffix);

    return filePathPointer;
}



_bool writeToOutputFile(int fileType, char* labelName, unsigned short address){
    FILE* fh;
    
    switch (fileType){
        case EXT_FILE:
            if ((fh = fopen(currentExtFile,"w+")) != NULL){
                if ((fprintf(fh,"%s\t0%o", labelName, address)) < 0){
                    handleError(CANT_WRITE_TO_EXT_FILE, currentExtFile);
                    fclose(fh);
                    return FALSE;
                }
            }
            else {
                perror(currentExtFile);
                return FALSE;
            }
            break;
        case ENT_FILE:
            if ((fh = fopen(currentEntFile,"w+")) != NULL){
                if((fprintf(fh,"%s\t0%o", labelName, address)) < 0 ){
                    handleError(CANT_WRITE_TO_ENT_FILE, currentEntFile);
                    fclose(fh);
                    return FALSE;
                }
            }
            else {
                perror(currentEntFile);
                return FALSE;
            }
            break;
        default:
            return FALSE;
    }
    fclose(fh);
    return TRUE;
}


 _bool writeObjectFileFirstRow(void){
     FILE* obFile;

     if ((obFile = fopen(currentObjFile,"w")) == NULL){
         perror(currentObjFile);
         return FALSE;
     }
     fprintf(obFile," %o %2o",getIC(),getDC());
     fclose(obFile);
     return TRUE;
 }



_bool writeToObjFile(unsigned short endCode, unsigned short endData){
    FILE* obfile;
    char linkerType;
    register unsigned short index;

    if ((obfile = fopen(currentObjFile,"w+")) == NULL){
        handleError(CANT_OPEN_OBJECT_FILE, currentObjFile);
        return FALSE;
    }
    resetIC();
    for(index = 0; index <= endCode;index++){
        switch (getCodeLinkerType(index)){
            case RELOCATBLE:
                linkerType = 'r';
                break;
            case EXTERNAL:
                linkerType = 'e';
                break;
            case ABSOLUTE:
                linkerType = 'a';
            default:
                handleError(CANT_WRITE_TO_OBJ_FILE,"no such linker address type");
        }
        if((fprintf(obfile,"0%2o 0%2o %2c", getIC(), getCode(index), linkerType)) < 0){
            handleError(CANT_WRITE_TO_OBJ_FILE, currentObjFile);
            fclose(obfile);
            return FALSE;
        }
        forward();
    }
    for (index = 0; index <= endData; index++){
        resetDC();
        if(fprintf(obfile,"0%2ohu 0%2ou", getDC() + getIC() - (unsigned short)1, *(getData())) < 0){
            handleError(CANT_WRITE_TO_OBJ_FILE, currentObjFile);
            fclose(obfile);
            return FALSE;
        }
        forwardDC();
    }
    fclose(obfile);
    return TRUE;
}


void initOutputFiles(char* filePath){
    unsigned fileNameSize;

    fileNameSize = strlen(filePath);

    currentObjFile = createFilePath(filePath, OBJ_FILE_SUFFIX);
    currentEntFile = createFilePath(filePath, ENT_FILE_SUFFIX);
    currentExtFile = createFilePath(filePath, EXT_FILE_SUFFIX);
 
}

