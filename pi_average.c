
//	pi_average.c is a program that will run
//	the pi estimation that uses the square
//	on multiple seeds and takes their average.
//
//	Created by Nicholas Chapman, 10-10-2026
//

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

//	PI_REFERENCE will be used to find
//	the variance of the estimation
//	and the average.
//
#define PI_REFERENCE 3.14159265359

//	Function Prototypes
//
void SetSeed(int seed);
double RandomPercent();
double DistanceFromCenter(double x, double y);
double CustomDistanceFromCenter(double x, double y);
double MakeEstimation(int dots, int seeds);

//	Sets the random seed
//
void SetSeed(int seed) {

	srand(seed);
}

//	Provides a random double from 0 to 1
//
double RandomPercent() {

	return ( (double)rand() / (double)RAND_MAX );
}

double DistanceFromCenter(double x, double y) {
	return hypot(x, y);
}

double CustomDistanceFromCenter(double x, double y) {	
	return sqrt(x*x+y*y);
}

//	Estimates the value of PI with values
//
double MakeEstimation(int dots, int seed) {

	SetSeed(seed);

	int i = 0;

	double x = 0;
	double y = 0;

	int n_hits = 0;
	
	while (i < dots) {

		x = RandomPercent();
		y = RandomPercent();

		if (DistanceFromCenter(x, y) <= 1) {
			n_hits += 1;
		}

		i++;
	}
	//
	return 4.0 * (double)( (double)n_hits / (double)dots );
}

//	Entry Point
//
int main(int argc, char** argv) {

	//	usage: <DOT_COUNT> <COUNT> [SEED_BASE]

	int dcount = 0;
	int ecount = 0;
	int seedBase = 1;

	if (argc != 3 && argc != 4) {
		printf("invalid. usage: <DOT_COUNT> <COUNT> [SEED_BASE]\n");
		return 1;
	}

	if (argc == 4)
		seedBase = atoi(argv[3]);
		
	dcount = atoi(argv[1]);
	ecount = atoi(argv[2]);

	//

	FILE* file = fopen("pi-average-report.txt", "w");
	if (file == NULL) {
		printf("failed to open file.\n");
		return 1;
	}

	time_t startTime = time(NULL);

	double currentEstimation = 0;
	double averageSum = 0;
	int currentSeed = seedBase;

	int i = 0;
	while (i < ecount) {

		SetSeed(currentSeed);
		
		currentEstimation = MakeEstimation(dcount, currentSeed);
		fprintf(file, "\tEstimation is %10lf at seed %d.\t(Variance: %10lf)\n", currentEstimation, currentSeed, PI_REFERENCE - currentEstimation);

		averageSum += currentEstimation;

		currentSeed++;
		i++;
	}

	time_t endTime = time(NULL);

	double avg = (double)averageSum / (double)ecount;

	fprintf(file, "Average estimation is: %10lf\t(Variance: %10lf)\n", avg, PI_REFERENCE - avg);

	fprintf(file, "\n\tProgram finished in about %10jd seconds", (intmax_t)difftime(endTime, startTime));

	fclose(file);
	
	return 0;
}
