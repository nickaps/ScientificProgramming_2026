
//	piecewise.c is a simple method of
//	programatically finding the area
//	under a particular function.
//	In this case we will have a piecewise
//	function and a custom user implemented
//	function.
//
//	Feel free to tinker with the code. I
//	have included several preprocessor flags
//	to experiment with.
//
//	The arguments for start, end, and precision
//	will default to 0, 4, and 1000000 respectively.
//	To change these arguments and experiment further,
//	run it with arguments from the command line.
//
//	usage: piecewise.exe <START> <END> [PRECISION]
//	                                 ___
//	   .- B          __              \  |  N       /  i * (B - A)   \       1       *We use Left Hand rectangular Riemann sum
//	  / 	f(x)dx   __      lim      )         f | ------------ + A |  x  ---
//	-'  A                  N -> inf. /__| i=0      \      N         /       N
//
//	Where:
//		A = <START>
//		B = <END>
//		N = [PRECISION]
//
//	Created by Nick Chapman, 10-5-2026
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//	To try other functions, replace the 'F_PIECEWISE'
//	with other flags:
//		F_PIECEWISE
//		F_SIN
//		F_COS
//		F_SQUARE
//		F_EXP		*natural exponential; uses base e
//		F_CONST
//		F_LIN
//		F_POLYN
//		F_ZERO
//		F_CUSTOM
//		|          |
#define F_PIECEWISE
//      |          |
//
#if defined F_PIECEWISE
	#define _FOFX PiecewiseFunction(x)
#elif defined F_CUSTOM
	#define _FOFX CustomFunction(x)
#elif defined F_SIN
	#define _FOFX sin(x)
#elif defined F_COS
	#define _FOFX cos(x)
#elif defined F_SQUARE
	#define _FOFX (x * x)
#elif defined F_EXP
	#define _FOFX exp(x)
#elif defined F_CONST
	#define _FOFX 2
#elif defined F_LIN
	#define _FOFX x
#elif defined F_POLYN
	#define _FOFX (-(x*x*x) - (x*x) + (3 * x) - 3)	//	Random polynomial courtesy of https://www.123calculus.com/en/random-polynomial-generator-page-1-60-140.html
#elif defined F_ZERO
	#define _FOFX 0
#endif

#if !defined _FOFX
	#define _FOFX 0
#endif
//
//	Practically speaking, all of the preprocessor flags above
//	should be placed in a separate header file. However, I
//	thought you would prefer it to be a single compilabe C
//	file, so I just opted to keep it far away from the rest
//	of the code.
//
 
//
//	Function Prototypes
//
double PiecewiseFunction(double x);
double CustomFunction(double x);
double _IntegratedFunction(double x);
double ComputeIntegral(double a, double b, int precision);
//
//	Function Implementations
//
double _IntegratedFunction(double x) {
	//	
	//	Modular function to be used as f(x) when
	//
	//	y = f x dx
	//
	//	...also:
	//
	//	    b .-
	//	y =	 /   f(x)dx
	//	   -' a
	//

	//	Returning Macro'd Function
	//
	return _FOFX;
}
//
double PiecewiseFunction(double x) {
														
	//	Based on the description in the assignment,
	//	I will stay true to the bounds at 0 and 4 so
	//	that whenever the function is outside of
	//	these boundaries it is equal to zero.
	//
	//	0 <= X < 2
	//
	if (0 <= x && x < 2) {
		return x + 2;		
	}
	//	2 <= X <= 4
	//
	else if (2 <= x && x <= 4) {
		return 4 - x;
	}
	//	X < 0 || X > 4
	//
	else {
		return 0;
	}
}
//
double CustomFunction(double x) {

	//	To be implemented.
	//
	//	Default fallback is 1:1 linear
	//
	return x;
}
//
double ComputeIntegral(double a, double b, int precision) {

	double x;
	double dx = (b - a) / precision;

	double sum = 0;
	
	for (x = a; x < b; x += dx) {
	
		sum += (dx * _IntegratedFunction(x));
	}

	return sum;
}
//
//	Entry Point
//
int main(int argc, char** argv) {

	double a = 0;
	double b = 4;
	int n = 1000000;

	if (argc == 4) {
		a = atof(argv[1]);
		b = atof(argv[2]);
		n = atoi(argv[3]);
	}
	else if (argc == 3) {
		a = atof(argv[1]);
		b = atof(argv[2]);
	}
	else if (argc != 1){
		printf("invalid. usage: <START> <END> [PRECISION]\n");
		printf("\tcall without arguments for default parameters.");
		return 1;
	}

	double sum = ComputeIntegral(a, b, n);

	printf("The integral from %.4lf to %.4lf of the given f(x) is:\t%.4lf\t(N=%d)\n", a, b, sum, n);

	return 0;
	
}
