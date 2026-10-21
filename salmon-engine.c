
//	salmon-engine.c will simply run the salmon
//	program with random values until terminated.
//
//	Created by Nick Chapman, 10-14-2026
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int GetGenerationSize() {
	return (int)(((double)rand() / (double)RAND_MAX) * 400);	//	20000 is max generation size
}

int main(int argc, char** argv) {

	double waitTime = 1.0;

	if (argc == 2) {
		waitTime = (double)atof(argv[1]);
	}
	else if (argc != 1) {
		printf("invalid. usage: salmon-engine [WAIT_TIME]\nparameter is optional; will default to 1 second.\n");
		return 1;
	}

	srand(time(NULL));
	GetGenerationSize();

	while (1) {
		time_t startTime = time(NULL);

		char buffer[75];

		sprintf(buffer, "salmon.exe %d", GetGenerationSize());

		system(buffer);

		while (waitTime > 0.0 && (double)difftime(time(NULL), startTime) < waitTime) {
			continue;
		}
		
	}

	return 0;
}
