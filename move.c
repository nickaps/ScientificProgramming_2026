
//	move.c 	is a simple program that will take the
//	path of a file and move it to another path.
//	Should work identically to the 'mv <target> <dir>'

#include <stdio.h>
#include <stdlib.h>

//	Function Prototypes
//
int TryCloseFile(FILE* f);
int CopyContent(FILE* from, FILE* to);

//	Function Implementations
//
int TryCloseFile(FILE* f) {
	if (f != NULL) {
		fclose(f);
		return 0;
	}
	return 1;
}

int CopyContent(FILE* from, FILE* to) {
	if (from == NULL || to == NULL) {
		printf("invalid. null pointer provided.");
		return 1;
	}

	char buffer[256];
	while (fgets(buffer, sizeof(buffer), from) != NULL) {
		fprintf(to, "%s", buffer);
	}

	return 0;
}


int main(int argc, char** argv) {

	//	Check args
	//
	if (argc != 3) {
		printf("invalid. usage: move.exe <target> <directory>\n");
		return 1;
	}

	//	Check if target file exists
	//
	FILE* file = fopen(argv[1], "r");
	if (file == NULL) {
		printf("invalid. file does not exist.\n");
		return 1;
	}

	FILE* fout = fopen(argv[2], "w");
	if (fout == NULL) {
		printf("invalid. output is invalid.");
		TryCloseFile(file);
		return 1;
	}

	//	Copy
	//
	CopyContent(file, fout);

	//	Close files
	//
	TryCloseFile(file);
	TryCloseFile(fout);

	//	Remove base file
	//
	remove(argv[1]);
	
	return 0;
}
