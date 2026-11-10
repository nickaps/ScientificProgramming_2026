
//	particles.c  is a program that will read
//	particles from a .csv file into an array of
//	particle structures to be able to perform
//	several operations on them.
//
//	Created by Nick Chapman, 10-28-2026
//

#include <stdio.h>
#include <stdlib.h>

//	Particle Struct
//
typedef struct {
	char*  name;		//	name - the name of the particle
	double mass;		//	mass - the mass of the particle in mega electron volts
	int spinClass;		//	spinClass - the spin of the particle is this number times one half. Class 1 are fermions and class 2 are bosons.
						//				Class 3 is the higgs boson and class 4 and greater are hypothesized.
	int charge;			//	charge - the positive or negative integer multiple of the magnitude of charge of an electron.
} Particle;


//	Function Prototypes
//
struct Particle** ReadCSV(char* fpath);


//	Function Implementations
//
struct Particle** ReadCSV(char* fpath) {

	FILE *fptr = fopen(fpath, "r");
	if (fptr == NULL) {
		printf("failed to open file at %s.\n", fpath);
		return NULL;
	}

	malloc 

	char buffer[256];

	while (fgets(buffer, sizeof(buffer), fptr) != NULL) {

		
		
	}
}
