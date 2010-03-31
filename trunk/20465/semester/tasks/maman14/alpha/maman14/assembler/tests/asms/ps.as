; file ps.as - includes main routine of reversing string "abcdef"

		.entry 		STDADD
		.entry		MAIN

		.extern		REVERSE	
		.extern		PTRSTR
		.extern		COUNT

STDADD:		.data		0
STR:		.string		"abcdef"
LASTCHAR:	.data		0
LEN:		.data		0

; count length of string, print the original string, reverse string, print reversed string.

MAIN:		lea		STR, STRADD
		jsr		COUNT
		jsr		PRTSTR
		mov		@STRADD, LASTCHAR
		add		LEN, LASTCHAR
		jsr		REVERSE
		jsr		PRTSTR
		hlt
