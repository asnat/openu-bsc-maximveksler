#include <stdio.h>


char * baseconv(unsigned int num, int base)
{
	static char retbuf[33];
	char *p;

	if(base < 2 || base > 16)
		return NULL;

	p = &retbuf[sizeof(retbuf)-1];
	*p = '\0';

	do {
		*--p = "0123456789abcdef"[num % base];
		num /= base;
	} while(num != 0);

	return p;
}

char * baseconvchar(unsigned char num, int base)
{
	static char retbuf[9];
	char *p;

	if(base < 2 || base > 16)
		return NULL;

	p = &retbuf[sizeof(retbuf)-1];
	*p = '\0';

	do {
		*--p = "0123456789abcdef"[num % base];
		num /= base;
	} while(num != 0);

	return p;
}

void charDict(int i, char* sign, unsigned char uChar, signed char sChar) {
    printf("======= %s%d ====\n", sign, i);
    printf("\tuChar = hex: %8x, dec = %4d, bin = %8s\n", uChar, uChar, baseconvchar(uChar, 2));
    printf("\tsChar = hex: %8x, dec = %4d, bin = %8s\n", sChar, sChar, baseconvchar(sChar, 2));
}

int main (int argc, char *argv[]) {
    unsigned char uChar;
    signed   char sChar;


    printf("EXAMPLE: Doing plus(+) / minus(-) operations on 8 bit signed & unsigned variables\n\
This examples shows are 2's complement, how signed variables are treated via the compiler vs the binary format.\n\
\nunsigned char uChar = 0;\n\
signed char sChar = 0;\n\n");
   
    int i;    

    printf("================================================================================\n");
    printf("======= PLUS(+) on uChar, sChar  ===============================================\n");
    printf("================================================================================\n");
    printf("\n"); 
    uChar = sChar = 0;
    for(i = 1; i <= 256; i++) {

        uChar +=1;
        sChar +=1;

        charDict(i, "+", uChar, sChar);
    }


    printf("\n\n\n\n");
    printf("=================================================================================\n");
    printf("======= MINUS(-) on uChar, sChar  ===============================================\n");
    printf("=================================================================================\n");
    printf("\n");
    uChar = sChar = 0;
    for(i = 1; i <= 256; i++) {
        uChar -=1;
        sChar -=1;

        charDict(i, "-", uChar, sChar);
    }


    return 0;
}

