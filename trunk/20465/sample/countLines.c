#include <stdio.h>

main() {
	long nl = 0;

	int c;
	while((c = getchar()) != EOF) {
		if(c == '\n')
			nl++;
	}

	printf("\n\nLine count= %ld\n", nl);

}
