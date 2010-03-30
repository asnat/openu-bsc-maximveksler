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

#define ADDRESS_OCT_FIXED_SIZE 3
#define DATA_OCT_FIXED_SIZE 6

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

static unsigned octal(unsigned number,unsigned* counter){
        unsigned result;

        if(number==0){
            (*counter)--;
            return number;
        }
        
        if(number/8 == 0){
            (*counter)--;
            result=number%8;
            return result;
        }
        result=(10*octal(number/8,counter))+number%8;
        (*counter)--;
        return result;
}

static void writeZeroToFile(unsigned zero,FILE* fh){
    unsigned i;

    if((fprintf(fh," "))<0)
        handleError(CANT_WRITE_TO_OBJ_FILE, NULL);

    for(i = 0; i<zero;i++){
        if((fprintf(fh,"0"))<0)
            handleError(CANT_WRITE_TO_OBJ_FILE, NULL);
    }
}

_bool writeToOutputFile(int fileType, char* labelName, unsigned short address){
    FILE* fh;
    
    switch (fileType){
        case EXT_FILE:
            if ((fh = fopen(currentExtFile,"w+")) != NULL){
                if ((fprintf(fh,"%s %6o\n", labelName, address)) < 0){
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
                if((fprintf(fh,"%s %6o\n", labelName, address)) < 0 ){
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


void writeToObjFile(){
    FILE* obfile;
    char linkerType;
    register unsigned short index;
    unsigned dataLineNum,octalNum,zeroCounter;
    unsigned short endCode, endData;

    if ((obfile = fopen(currentObjFile,"w+")) == NULL){
        handleError(CANT_OPEN_OBJECT_FILE, currentObjFile);
    }

    endCode = getIC();
    endData =getDC();
    fprintf(obfile,"%7o", endCode);
    fprintf(obfile,"%4o\n", endData);


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

            zeroCounter = ADDRESS_OCT_FIXED_SIZE;
            octalNum = octal(index, &zeroCounter);
            writeZeroToFile(zeroCounter, obfile);
            if((fprintf(obfile,"%u",octalNum))<0){
                handleError(CANT_WRITE_TO_OBJ_FILE, currentObjFile);
                fclose(obfile);
            }

            zeroCounter = DATA_OCT_FIXED_SIZE;
            octalNum = octal(getCode(index),&zeroCounter);
            writeZeroToFile(zeroCounter, obfile);
            if((fprintf(obfile,"%u",octalNum))<0){
                handleError(CANT_WRITE_TO_OBJ_FILE, currentObjFile);
                fclose(obfile);
            }

            if((fprintf(obfile,"%2c\n",linkerType))<0){
                handleError(CANT_WRITE_TO_OBJ_FILE, currentObjFile);
                fclose(obfile);
            }
        }
    }

    if(endData > 0){
        for (index = 0; index < endData; index++){
            dataLineNum = (index + endCode );

            zeroCounter = ADDRESS_OCT_FIXED_SIZE;
            octalNum = octal(dataLineNum, &zeroCounter);
            writeZeroToFile(zeroCounter, obfile);
            if((fprintf(obfile,"%u",octalNum))<0){
                handleError(CANT_WRITE_TO_OBJ_FILE, currentObjFile);
                fclose(obfile);
            }

            zeroCounter = DATA_OCT_FIXED_SIZE;
            octalNum = octal(getData(index),&zeroCounter);
            writeZeroToFile(zeroCounter, obfile);
            if((fprintf(obfile,"%u\n",octalNum))<0){
                handleError(CANT_WRITE_TO_OBJ_FILE, currentObjFile);
                fclose(obfile);
            }
        }
    }

    fclose(obfile);
}

void freeFilesPathPointers(){
    free(currentEntFile);
    free(currentExtFile);
    free(currentObjFile);
}


void initOutputFiles(char* filePath){
    unsigned fileNameSize;

    fileNameSize = strlen(filePath);

    currentObjFile = createFilePath(filePath, OBJ_FILE_SUFFIX);
    currentEntFile = createFilePath(filePath, ENT_FILE_SUFFIX);
    currentExtFile = createFilePath(filePath, EXT_FILE_SUFFIX);
 
}

