
//	serial-rename.c		is a simple program that will take
//	a directory of files and then parse and rename them
//	so that it replaces the number in the beginning to
//	be up to date.
//
//	e.g. 	from: 001 File A, 002 File B, 004 File D
// 			to  : 001 File A, 002 File B, 003 File D
//
//	Created by Nick Chapman, 9-21-2026

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	
	if (argc != 2) {
		printf("invalid. usage: serial-rename.exe <working-directory>\n");
		return 1;
	}
	
	return 0;
}
