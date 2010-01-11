/* 
 * File:   source.c
 * Author: Maxim Veksler 303856983
 *
 * Created on January 9, 2010, 5:00 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <string.h>

#define INPUT_BUFFER 1024

/**
 * This function return up to where the original string should be copied before appending the ".c" string.
 * The rational is that if a `valid` . position was found we will return string lenght that will casuse 
 * coping of character up to this location (exclusive).
 *
 * Dot (.) Seeking alghoritem works as following:
 * 1. If (dot was found in string)
 *   1. If dot was found after last '/' OR path has no '/' in it := return length up to dot (exclusive)
 *   else := return full string lenght
 * else:= return full string lenght.
 *
 */ 
int calculateWindowsSuffixLocation(char* executable_path) {
    char *lastSlash_substr;
    char *lastDot_substr;

    int totalLength;
    int lastSlashPos;
    int lastDotPos;

    totalLength = strlen(executable_path);

    lastSlash_substr = strchr(executable_path, '/');
    lastDot_substr = strchr(executable_path, '.');

    if(lastDot_substr != NULL) {
        lastDotPos = totalLength - strlen(lastDot_substr);
        
        if(lastSlash_substr != NULL) {
            /* We have both "." and "/" => path is either relative or absolute
             * In that case we want to cut the last dot only if it it's part of
             * the application name itself.
	     */
            lastSlashPos = totalLength - strlen(lastSlash_substr);
            if(lastSlashPos < lastDotPos) {
                /* The "." is actually part of the application name, we know it 
                 * because it is positioned after the last "/", hence we return
                 * it position so that we can ignore it.
                 */
                return lastDotPos;
            } else {
		return totalLength;
 	    }
        } else {
            /* We haven't found a single "/" in the path name, meaning that
             * application name contains "."
             */
            return lastDotPos;
        }
    } else {
        /* haven't found a dot at all, return the full length of the string
         * as we need to take it all.
         */
        return totalLength;
    }

    /* Should never reach here... */
    return 0;
}

/**
 * It is assumed that application is running on UNIX OS...
 *
 * This function will return the correct file name path concatenatde with ".c" so that we can print it.
 */
char *getSourceFileName(char* executable_path) {
    char *filename;
    
    int calculateSuffixLocation;
    int strIndex;

    calculateSuffixLocation = calculateWindowsSuffixLocation(executable_path);

    filename = malloc(calculateSuffixLocation + 3); /* We add 3 because we need to add ".c\0" as suffix */

    for(strIndex=0; strIndex < calculateSuffixLocation; strIndex++) {
        filename[strIndex] = executable_path[strIndex];
    }

    filename[strIndex++] = '.';
    filename[strIndex++] = 'c';
    filename[strIndex] = '\0';

    return filename;
}

/**
 * In the spirit of strcpy copy a file from specificed path on the hard drive
 *  supplied by the parameter filename to a FILE pointer given by the
 *  parameter fp
 */
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
 * Main for source application.
 *
 * The code identified it's running path, based on calculated path logic 
 * decided where the ".c" concatenation should go then printed the 
 * file pointed by the concatenatde string to stdout.
 */
int main(int argc, char** argv) {
    char *filename;

    filename = getSourceFileName(argv[0]);
    
    strfilecpy(stdout, filename);
    
    free(filename);
    return (EXIT_SUCCESS);
}

