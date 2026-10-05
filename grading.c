
//	grading.c	will showcase the if-else statements
//	by checking if a given score is greater than
//	a certain value, giving us a pass/fail. Also
//	support for fair grading will be available.
//
//	Created by Nick Chapman, 9-30-2026
//

#include <stdio.h>
#include <stdlib.h>

void grading_fair(unsigned char score) {

	char *grade = "AB";
	
	if (score <= (unsigned char)50) {
		grade = "F";
	}
	else if (score > (unsigned char)50 && score < (unsigned char)70) {
		grade = "D";
	}
	else if (score >= (unsigned char)70 && score < (unsigned char)76) {
		grade = "C";
	}
	else if (score >= (unsigned char)76 && score < (unsigned char)80) {
		grade = "C+";
	}
	else if (score >= (unsigned char)80 && score < (unsigned char)86) {
		grade = "B";
	}
	else if (score >= (unsigned char)86 && score < (unsigned char)90) {
		grade = "B+";
	}
	else if (score >= (unsigned char)90 && score < (unsigned char)98) {
		grade = "A";
	}
	else if (score >= (unsigned char)98) {
		grade = "A+";
	}

	printf("You got a(n) %s in the class.\n", grade);
}

void grading_unfair(unsigned char score) {
	if (score >= (unsigned char)93) {
		printf("You passed the course!\n");
	}
	else {
		printf("You are an utter failure. What a disappointment...\n");
	}
}

int main (int argc, char** argv) {

	if (argc != 2) {
		printf("invalid. usage: grading.exe <score>\n");
		return 1;
	}

	int i = atoi(argv[1]);
	if (i < 0 || i > 100) {
		printf("invalid. must enter score between 0 and 100.");
		return 1;
	}

	unsigned char value = (unsigned char)i;
	//grading_unfair(value);
	grading_fair(value);
	
	return 0;
	
}
