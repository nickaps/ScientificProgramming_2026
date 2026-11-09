
//	salmon.c is a simple simulation that will
//	assess the survivability of a generation
//	of salmon swimming upstream.
//
//	Created by Nick Chapman, 10-14-2026
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//	Function Prototypes
//
void SetSeed(double seed);
double RandomPercentage();
void AffectGeneration(int* generation, double riskPercent, char* description);

//	Function Implementations
//
//	 Set the seed using srand()
//
void SetSeed(double seed) {
	srand(seed);
}
//
//	 Return a random percentage
//
double RandomPercentage() {
	return ( (double)rand() / (double)RAND_MAX);
}
//
//	 Adjusts a number according to chance
//
void AffectGeneration(int* generation, double riskPercent, char* description) {

	if (*generation <= 0) return;

	if (riskPercent > 1.0 || riskPercent < 0.0) {
		printf("invalid. riskPercent must be between 0 and 1.\n");
		return;
	}

	double coin = 0.0;

	for (int i = 0; i < *generation; i++) {
		coin = RandomPercentage();
		if (coin > riskPercent) {
			*generation -= 1;
		}
	}

	printf("Salmon count after %30s (%lf%% Risk) :\t%d\n", description, riskPercent, *generation);

	if (*generation == 0) {
		printf("Your Salmon have perished!\n");
	}
}

//	Entry point
//
int main(int argc, char** argv) {

	int salmonCount = 100;
	
	if (argc == 2) {
		salmonCount = atoi(argv[1]);
	}
	else if (argc != 1) {
		printf("invalid. usage: salmon [GENERATION_SIZE]\nparameter is optional; defaults to 100.\n");
		return 1;
	}

	//	Set seed using system time
	//
	SetSeed(time(NULL));

	//	Display start count
	//
	printf("\tInitial Size of Generation: %10d\n", salmonCount);

	//	Calculate Loss
	//
	AffectGeneration(&salmonCount, 0.20, "The Estuary Fishing Net");
	AffectGeneration(&salmonCount, 0.15, "The River Rapids");
	AffectGeneration(&salmonCount, 0.30, "The Bear Shallows");
	AffectGeneration(&salmonCount, 0.25, "The Hydroelectric Dam");
	AffectGeneration(&salmonCount, 0.10, "The Eagle Canyon");

	if (salmonCount > 0) {
		printf("Congratulations! Your Salmon have survived their treacherous journey.\n");
	}
		
	//	Success!
	return 0;
}
