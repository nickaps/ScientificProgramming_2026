
//	integrate.c 	will be used to take
//	the Riemann sum of a function.
//	a.k.a. the area under the curve.
//
//	Created by Nicholas Chapman, 9-23-2026
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//	Arbitrary sampe function to integrate.
//	Feel free to replace with any function in
//	order to find the definite integral.
//
double f(double _x) {
	return _x * _x;

	//return sin(_x);
}

//	Left Hand integral
//
double integrate_left(int _n, double _s, double _e) {
	double dx = (_e - _s) / _n;
	double x = _s;

	double sum = 0;

	while (x < _e) {
		sum += dx * f(x);
		x += dx;
	}

	return sum;
}

//	Right Hand integral
//
double integrate_right(int _n, double _s, double _e) {
	double dx = (_e - _s) / _n;
	double x = _s;

	double sum = 0;

	while (x <= _e) {
		x += dx;
		sum += dx * f(x);
	}

	return sum;
}

//	Mid Point integral
//
double integrate_mid(int _n, double _s, double _e) {
	double dx = (_e - _s) / _n;
	double x = dx / 2;
	double fomp = 0;

	double sum = 0;

	while (x <= _e) {
		fomp = f(x);
		sum += fomp * dx;
		x += dx;
	}

	return sum;
}

//	Trapezoid integral
//
double integrate_trapezoid(int _n, double _s, double _e) {
	double dx = (_e - _s) / _n;
	double x = 0;

	double lh = 0;
	double rh = 0;

	double sum = 0;
	
	while (x <= _e) {
		rh = f(x);
		sum += ((lh + rh) * dx) / 2.0;
		lh = rh;
		x += dx;
	}

	return sum;
}

//	Entry Point
//
int main(int argc, char** argv) {

	if (argc != 4) {
		printf("invalid. usage: integrate.exe <precision-value> <start> <end>\n");
		return 1;
	}

	int n = atoi(argv[1]);

	double start = atof(argv[2]);
	double end = atof(argv[3]);

	printf("Definite LH integral from %lf to %lf of f(x) is %lf.\n", start, end, integrate_left(n, start, end));
	printf("Definite RH integral from %lf to %lf of f(x) is %lf.\n", start, end, integrate_right(n, start, end));
	printf("Definite MP integral from %lf to %lf of f(x) is %lf.\n", start, end, integrate_mid(n, start, end));
	printf("Definite TZ integral from %lf to %lf of f(x) is %lf.\n", start, end, integrate_trapezoid(n, start, end));

	return 0;
}
