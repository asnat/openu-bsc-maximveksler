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

#define ADDRESS_OCT_FIXED_SIZE 4
#define DATA_OCT_FIXED_SIZE 6

static char* currentObjFile;
static char* currentExtFile;
static char* currentEntFile;

/* create the output file path pointer */
static char* createFilePath(char* filePrefix, const char* suffix){

    char* filePathPointer;

    /* create the file path poiinter */
    filePathPointer = malloc(strlen(filePrefix) * sizeof(char) + strlen(suffix) * sizeof(char));
    strcpy(filePathPointer,filePrefix);
    strcat(filePathPointer,suffix);

    return filePathPointer;
}

/* recursive function to convert decimal to octal, and store a counter of needed zero to print before the number */
static unsigned octal(unsigned number,unsigned* counter){
        unsigned result;

        /* if decimal is 0, return the number with less 1 one zero before */
        if(number==0){
            (*counter)--;
            return number;
        }

        /* the end recursive condition, if number/8 is 0 */
        if(number/8 == 0){
            (*counter)--;
            result=number%8;
            return result;
        }

        /* store the reminder in result but oposite, from last to first */
        result=(10*octal(number/8,counter))+number%8;
        (*counter)--;
        return result;
}

/* print zero to object file */
static void writeZeroToFile(unsigned zero,FILE* fh){
    unsigned i;

    if((fprintf(fh," "))<0)
        handleError(CANT_WRITE_TO_OBJ_FILE, NULL);

    for(i = 0; i<zero;i++){
        if((fprintf(fh,"0"))<0)
            handleError(CANT_WRITE_TO_OBJ_FILE, NULL);
    }
}

/* write the to EXT and ENT output files */
_bool writeToOutputFile(int fileType, char* labelName, unsigned short address){
    FILE* fh;

    /* check the file type*/
    switch (fileType){
        /* if file type EXT, print to the .ext file */
        case EXT_FILE:
            if ((fh = fopen(currentExtFile,"a")) != NULL){
                if ((fprintf(fh,"%-10s %10o\n", labelName, address)) < 0){
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

        /* if file type ENT, print to .ent file */
        case ENT_FILE:
            if ((fh = fopen(currentEntFile,"a")) != NULL){
                if((fprintf(fh,"%-10s %-10o\n", labelName, address)) < 0 ){
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
        /* if unknown file type return error */
        default:
            return FALSE;
    }
    fclose(fh);
    return TRUE;
}

/* write code and dat segment to .ob file */
void writeToObjFile(){
    FILE* obfile;
    char linkerType; /* the linker type for printing */
    register unsigned short index; /* index to current line in the code/data segment to priint */
    unsigned dataLineNum,octalNum,zeroCounter;
    unsigned short endCode, endData; /* the first empty line in the code/data segment */

    if ((obfile = fopen(currentObjFile,"w+")) == NULL){
        handleError(CANT_OPEN_OBJECT_FILE, currentObjFile);
        return;
    }

    /* init the end point for printind code segment */
    endCode = getIC();
    /* init the end point for printind code segment */
    endData =getDC();

    /* print the first row of the object file, the sum of code segment rows and the sum of data segment rows */
    fprintf(obfile,"%10o", endCode);
    fprintf(obfile,"%10o\n", endData);

    /* write to object file from the code segment only if there is something to write */
    if (endCode > 0){

        /* print each line*/
        for(index = 0; index < endCode;index++){
            /* identify the linker type to print */
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

            /* set the fix size of address number */
            zeroCounter = ADDRESS_OCT_FIXED_SIZE;
            /* convert the address to octal and find how many zero to add in the begining */
            octalNum = octal(index, &zeroCounter);
            /* write the begining zero */
            writeZeroToFile(zeroCounter, obfile);
            /* print the address*/
            if((fprintf(obfile,"%u",octalNum))<0){
                handleError(CANT_WRITE_TO_OBJ_FILE, currentObjFile);
                fclose(obfile);
            }

            /* set the fix size of command */
            zeroCounter = DATA_OCT_FIXED_SIZE;
            /* convert the command to octal and find how many zero to add in the begining */
            octalNum = octal(getCode(index),&zeroCounter);
            /* write the begining zero */
            writeZeroToFile(zeroCounter, obfile);
            /* print the command in octal */
            if((fprintf(obfile,"%u",octalNum))<0){
                handleError(CANT_WRITE_TO_OBJ_FILE, currentObjFile);
                fclose(obfile);
            }

            /* print the linker type of the row */
            if((fprintf(obfile,"%10c\n",linkerType))<0){
                handleError(CANT_WRITE_TO_OBJ_FILE, currentObjFile);
                fclose(obfile);
            }
        }
    }

    /* print the data segment to the object file only if there is any data lines */
    if(endData > 0){
        for (index = 0; index < endData; index++){
            /* set the address in the data lines */
            dataLineNum = (index + endCode );

            /* set the fix size of address */
            zeroCounter = ADDRESS_OCT_FIXED_SIZE;
            /* convert the address to octal and find how many zero to add in the begining */
            octalNum = octal(dataLineNum, &zeroCounter);
            /* write the begining zero */
            writeZeroToFile(zeroCounter, obfile);
            /* print the address in octal */
            if((fprintf(obfile,"%u",octalNum))<0){
                handleError(CANT_WRITE_TO_OBJ_FILE, currentObjFile);
                fclose(obfile);
            }

            /* set the fix size of data */
            zeroCounter = DATA_OCT_FIXED_SIZE;
            /* convert the data to octal and find how many zero to add in the begining */
            octalNum = octal(getData(index),&zeroCounter);
            /* write the begining zero */
            writeZeroToFile(zeroCounter, obfile);
            /* print the data in octal */
            if((fprintf(obfile,"%u\n",octalNum))<0){
                handleError(CANT_WRITE_TO_OBJ_FILE, currentObjFile);
                fclose(obfile);
            }
        }
    }

    fclose(obfile);
}

/* this function free the output files pointers of the current file */
void freeOutputFiles(){
    if(currentEntFile != NULL)
        free(currentEntFile);

    if(currentExtFile != NULL)
        free(currentExtFile);

    if(currentObjFile != NULL)
        free(currentObjFile);
}

/* the function set the output files pointers of the current file */
void initOutputFiles(char* filePath){
    unsigned fileNameSize;

    fileNameSize = strlen(filePath);

    currentObjFile = createFilePath(filePath, OBJ_FILE_SUFFIX);
    currentEntFile = createFilePath(filePath, ENT_FILE_SUFFIX);
    currentExtFile = createFilePath(filePath, EXT_FILE_SUFFIX);
 
}

/* Utility to delete files if error happens */
void removeOutputFiles() {
    remove(currentObjFile);
    remove(currentEntFile);
    remove(currentExtFile);
}