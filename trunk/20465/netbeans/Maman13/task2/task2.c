/* 
 * File:   task2.c
 * Author: hq4ever
 *
 * Created on January 9, 2010, 5:00 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <string.h>

#define INPUT_BUFFER 1024

char *getSourceFileName(char* abs_executable_path) {
    //char *executable_path = strrchr(abs_executable_path, '/');
    char *filename;
    
    int abs_executable_path_len;
    int strIndex;

    abs_executable_path_len = strlen(abs_executable_path);

    filename = malloc(abs_executable_path_len + 3); // We add 3 because we need to add ".c\0" as suffix

    for(strIndex=0; strIndex < abs_executable_path_len; strIndex++) {
        filename[strIndex] = abs_executable_path[strIndex];
    }

    filename[strIndex++] = '.';
    filename[strIndex++] = 'c';
    filename[strIndex] = '\0';

    return filename;
}

void strfilecpy(FILE *fp, char *filename) {
    FILE *file = fopen ( filename, "r" );
   if ( file != NULL ) {
      char line [ INPUT_BUFFER ];

      while ( fgets ( line, INPUT_BUFFER, file ) != NULL ) { /* read a line */
         fputs ( line, fp ); /* write the line */
      }
      fclose ( file );
   } else {
      perror ( filename ); /* why didn't the file open? */
   }
}

/*
 * 
 */
int main(int argc, char** argv) {
    char *filename;

    filename = getSourceFileName(argv[0]);
    
    strfilecpy(stdout, filename);
    
    free(filename);
    return (EXIT_SUCCESS);
}

