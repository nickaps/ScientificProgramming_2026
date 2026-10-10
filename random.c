
//	random.c is a demonstration of
//	pseudo-random number generation.
//
//	Created by Nick Chapman, 10-9-2026
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

	if (argc != 3) {
		printf("invalid. usage: random <COUNT> <SEED>\n");
		return 1;
	}

	int count = atoi(argv[1]);
	int seed = atoi(argv[2]);

	srand(seed);

	for (int i = 0; i < count; i++)
	{
		printf("%lf\n", (double)((double)rand() / (double)RAND_MAX));
	}

	return 0;
}
