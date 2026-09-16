#include <stdio.h>
#include <stdlib.h>

int main (int argc, char** argv) {
        
    //      Check if there are less than three arguments. The name of the .exe, and at
    //      least two numbers must be present in order to perform addition.
    //
	if (argc < 3) {
		printf("invalid. must be provided multiple numbers to add together.\n");
		return 1;
	}
	
    //      Initialize buffer to store all arguments in one string.
    //
	char buffer[100] = {0};
        

    //      Allocate compound sum on stack memory
    //
	int cmpdsum = 0;
	for ( int i = 1; i < argc; i++) {
        //      Integer from ASCII
        //
		int froma = atoi(argv[i]);

        //      Check if conversion from ASCII fails
        //
		if (froma == 0) break;

        //      Add to compound sum
        //
		cmpdsum += froma;

        //      If i is at the end of the list then add an 'and ' before
        //      the string gets appended. If there are more to be read then
        //      simply add it to the buffer.
		if (i == argc - 1) sprintf(buffer, "%sand %s", buffer, argv[i]);
		else sprintf(buffer, "%s%s ", buffer, argv[i]);
	}
	printf("the sum of %s is %d", buffer, cmpdsum);
	return 0;
}
