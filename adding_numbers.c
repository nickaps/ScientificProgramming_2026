#include <stdio.h>
#include <stdlib.h>

int main (int argc, char** argv) {
		
	if (argc < 3) {
		printf("invalid. must be provided multiple numbers to add together.\n");
		return 1;
	}
	
	char buffer[100] = {0};

	int cmpdsum = 0;
	for ( int i = 1; i < argc; i++) {
		int froma = atoi(argv[i]);
		if (froma == 0) break;
		cmpdsum += froma;
		if (i == argc - 1) sprintf(buffer, "%sand %s", buffer, argv[i]);
		else sprintf(buffer, "%s%s ", buffer, argv[i]);
	}
	printf("the sum of %s is %d", buffer, cmpdsum);
	return 0;
}
