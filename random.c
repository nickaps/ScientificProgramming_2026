
//	random.c is a demonstration of
//	pseudo-random number generation.
//
//	Created by Nick Chapman, 10-9-2026
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

	if (argc != 2) {
		printf("invalid. usage: random <COUNT>\n");
		return 1;
	}

	int count = atoi(argv[1]);

	for (int i = 0; i < count; i++)
	{
		
	}
}
