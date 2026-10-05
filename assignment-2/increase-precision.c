
//	increase-precision.c will take a max precision amount and an
//	optional step amount, and start printing integral values.
//
//	Created by Nick Chapman, 10-5-2026
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32)
	#define COMMAND_START "piecewise.exe"
	#define PAUSE_PROGRAM system("pause")
#else
	#include <unistd.h>
	#define COMMAND_START "./piecewise.exe"
	#define PAUSE_PROGRAM pause();
#endif

int main(int argc, char** argv) {

	int max = 25;
	int step = 1;

	double start = 0;
	double end = 4;

	if (argc == 5) {
		start = atof(argv[1]);
		end = atof(argv[2]);
		max = atoi(argv[3]);
		step = atoi(argv[4]);
	}
	else if (argc == 3) {
		max = atoi(argv[1]);
		step = atoi(argv[2]);
	}
	else if (argc == 2) {
		max = atoi(argv[1]);
	}else if (argc != 1) {
		printf("invalid. usage: increase-precision.exe <START> <END> <MAX> <STEP>\n");
		printf("\talso: increase-precision.exe <MAX> <STEP>\n");
		return 1;
	}

	char buffer[100];

	int current = 1;
	while (current < max) {
		snprintf(buffer, sizeof(buffer), "%s %lf %lf %d", COMMAND_START, start, end, current);
		system(buffer);

		memset(buffer, '\0', sizeof(buffer));
		
		current += step;
	}

	//	Pause at the end
	//
	PAUSE_PROGRAM;

	return 0;
}
