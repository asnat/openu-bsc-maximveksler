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

    filePathPointer = malloc(strlen(filePrefix) * sizeof(char) + strlen(suffix) * sizeof(char));
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
                if ((fprintf(fh,"%s\t0%o\n", labelName, address)) < 0){
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
                if((fprintf(fh,"%s\t0%o\n", labelName, address)) < 0 ){
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
     fprintf(obFile," %o %2o\n",getIC(),getDC());
     fclose(obFile);
     return TRUE;
 }



_bool writeToObjFile(){
    FILE* obfile;
    char linkerType;
    register unsigned short index;
    unsigned code,data, dataLineNum;
    unsigned short endCode, endData;

    if ((obfile = fopen(currentObjFile,"w+")) == NULL){
        handleError(CANT_OPEN_OBJECT_FILE, currentObjFile);
        return FALSE;
    }

    endCode = getIC();
    endData =getDC();
    fprintf(obfile,"%5o", endCode);
    fprintf(obfile,"%2o\n", endData);


    if (endCode > 0){
        for(index = 0; index < endCode;index++){
            switch (getCodeLinkerType(index)){
                case RELOCATBLE:
                    linkerType = 'r';
                    break;
                case EXTERNAL:
                    linkerType = 'e';
                    break;
                case ABSOLUTE:
                    linkerType = 'a';
                    break;
                default:
                    handleError(CANT_WRITE_TO_OBJ_FILE,"no such linker address type");
            }
            code = getCode(index);
            if((fprintf(obfile,"0%o 0%o %c\n", index, getCode(index), linkerType)) < 0){
                handleError(CANT_WRITE_TO_OBJ_FILE, currentObjFile);
                fclose(obfile);
                return FALSE;
            }
            forward();
        }
        endCode--;
    }
    if(endData > 0){
        for (index = 0; index <= endData; index++){
            dataLineNum = (index + endCode );
            data = getData(dataLineNum);
            if(fprintf(obfile,"0%o 0%o\n", dataLineNum  , getData(dataLineNum)) < 0){
                handleError(CANT_WRITE_TO_OBJ_FILE, currentObjFile);
                fclose(obfile);
                return FALSE;
            }
            forwardDC();
        }
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

