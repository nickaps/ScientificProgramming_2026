
//	pi.c is a program used to estimate the
//	value of pi with a dpi method of finding
//	area.
//
//	Created by Nick Chapman, 10-9-2026
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <time.h>

double DistanceFromCenter(double x, double y) {
	return hypot(x, y);
}

double RandPercent() {
	int rint = rand();
	return (double)((double)rint / (double)RAND_MAX);
}

int main(int argc, char** argv) {

	if (argc != 3) {
		printf("invalid. usage: pi <DOT_COUNT> <SEED>\n");
		return 1;
	}

	int dcount = atoi(argv[1]);
	unsigned int seed = (unsigned int)atoi(argv[2]);

	srand(seed);

	int i = 0;
	
	double x = 0;
	double y = 0;
	double distance = 0;

	int n_hit = 0;

	while (i < dcount) {

		x = RandPercent();
		y = RandPercent();
		
		distance = DistanceFromCenter(x, y);

		if (distance <= 1) {
			//	Hit
			n_hit += 1;
		}
		i++;
	}

	double estimation = ((double)n_hit / (double)dcount) * 4;

	printf("The constant PI is estimated at: %lf\n", estimation);

	return 0;
}
