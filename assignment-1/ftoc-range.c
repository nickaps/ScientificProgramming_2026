
//	ftoc-range.c	will take arguments from the user, otherwise
//	it will prompt them for numerical input. Computer will	
//	check to make sure input is number, and then it will
//	print a table of Faranheit values increasing by five
//	along side their Celcius counterparts. 
//
//	Created by Nick Chapman, 9-18-2026
//
//	NOTES:
//		- use format specifier like this for table: ""%10d"
//		  the 10 after the % will always provide at least 10
//		  spaces in the console.
//		
//		- '.'   :     46,
//		- '0-9' : 48 - 57
//				:
//		  char  :   ASCII
//

#include <stdio.h>
#include <stdlib.h>


//	Function Prototypes
//
int isNumeric(char* s, double *output);
double ftoc(double f);
void ftocList(double base_f, int iterations);


//	Function Implementations
//
//	Checks if a number is numeric, and, if so, returns the number to 'output'
//
int isNumeric(char* s, double *output) {

	//	Will parse a string to check if each digit
	//	is actually part of a number string.

	//	dpcount will increment for every '.' found.
	//
	int dpCount = 0;
	int asciiValue = 0;
	
	char* cursor = s;
	while (*cursor != '\0') {
		asciiValue = (char)*cursor;
		if (asciiValue == 46)
			dpCount += 1;

		//	10,123a456.00022.00
		//	  ^    ^ invalid ^
		//	Only if it is not a decimalPoint, comma, or is not between 0 and 9,
		//	or we have counted more than one decimal point.
		//
		if ( (asciiValue != 46 && (asciiValue > 57 || asciiValue < 48)) || dpCount > 1 ) {
			// Error flag
			return 1;
		}

		cursor++;
	}

	//	At this point, string must be numeric
	//
	*output = atof(s);

	//	Success flag
	return 0;
}


//	Converts degrees Faranheit into degrees Celcius
//
double ftoc(double f) {
	return  ((f - 32.0) * 5.0) / 9.0;
}

//	Takes a base degrees in Faranheit, and a number
//	of iterations, and then prints a table with
//	as many steps of five f then coverting to c.
//		
void ftocList(double f, int iterations) {

	printf("\n\t|    Faranheit\t   Celcius  |\n");
	printf("\t|***************************|\n");
	double tmp = 0.0;
	
	for (int i = 0; i < iterations + 1; i++) {

		tmp = (i * 5) + f;
		
		printf("\t| %11.2lf\t%11.2lf |\n", tmp, ftoc(tmp));
	}
}

//	Entry point
//
int main (int argc, char** argv) {

	//	Pointer to whichever string is being used for input
	//
	char* instring = NULL;
	int iterations = 4;

	//	First, test if there are too many or too few arguments
	//
	if (argc > 3 || argc < 0) {	//	Having an argc less than one is practically impossible, but I don't trust QA.
		printf("invalid. usage: ftoc-range.exe <degrees-faranheit> [iterations; default: 4] || ftoc-range.exe\n");
		printf("		 [ .. ] is optional. if no arguments, program will prompt user for degrees.\n");
		return 1;
	}
	//	Second, if there are no provided arguments
	//
	else if (argc == 1) {
		//	Goto the Prompt User header
		//
		goto PROMPT_USR;	
	}
	//	Third Option is if there are exactly two arguments
	//
	else if (argc == 2) {
		//	Sets instring to first argument
		//
		instring = argv[1];
	}
	//	Then Lastly, if you want to change the amount of iterations.
	//	Default additional iterations is set to 4, which displays 5 conversions.
	//	This is the value being changed with three agruments.
	//
	else if (argc == 3) {
		//	Sets instring to first argument
		//
		instring = argv[1];

		//	Sets number of iterations if not NaN
		//
		int tmp = atoi(argv[2]);
		if (tmp > 0) {
			iterations = tmp;
		}
	}

	//	Use for when returning from prompt
	//
	PROMPT_RETURN:
	//

	//	Initialize degrees faranheit
	//
	double deg_f = 0.0;
	//
	//	Check to make sure it is numeric, then translate from string to double
	//
	if (isNumeric(instring, &deg_f) == 1) {
		printf("invalid. must provide numerical input (e.g. \"1,203.0\")\n");
		return 1;
	}

	//	Convert and print list of numbers.
	ftocList(deg_f, iterations);

	//	Happy ending :)
	//
	return 0;

	//	Use for when prompting
	//
	PROMPT_USR:
	//
	
	//	Prompt user for input in Faranheit
	//	
	char buffer[50];
	printf("Enter degrees in Faranheit: ");
	scanf("%s", buffer);
	//
	//	Sets instring to the user input
	//
	instring = buffer;

	//	Return to continue program
	//
	goto PROMPT_RETURN;
	
}
