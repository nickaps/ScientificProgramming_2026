
//	A program that will provide the average value
//	for each row of a .csv file.
//
//	Created by Nick Chapman, 9-16-2026

#include <stdio.h>
#include <stdlib.h>

//	A LinkedList node going rightwards on .csv table
//	Contains double type value and points to next in row.
//
struct ColumnNode {
	struct ColumnNode* next;
	double value;
};

//	A LinkedList node going downwards on .csv table
//	Contains RowNode* head node for row and poitns
//	to next down.
//
struct RowNode {
	struct RowNode* next;
	struct ColumnNode* head;
	struct ColumnNode* tail;
	int width;
};

//	Table struct contains a head and tail
//	row pointer and current width and
//	height.
//
struct Table {
	struct RowNode* head;
	struct RowNode* tail;
	int depth;
};


//	Function Prototypes
//
struct Table* ParseCSVTable(const char *directory);
void AddToRow(struct Table* table, double value);
void NewRow(struct Table* table);
void FreeTable(struct Table* table);

//	Funciton Implementations
//
struct Table* ParseCSVTable(const char *directory) {

	//	Dynamically allocate memory for newTable
	//
	struct Table* newTable = malloc(sizeof(struct Table));
	newTable->head = NULL;
	newTable->tail = NULL;
	newTable->depth = 0;
	
	//	Initialize buffer to read lines to
	//
	char buffer[512];

	//	Set filePtr to the .csv file
	//
	FILE *filePtr = fopen(directory, "r");

	//	Check to see if open was successful
	//
	if (filePtr == NULL) {
		printf("failed to open file.\n");
		return NULL;
	}

	//	Read line by line
	while (fgets(buffer, sizeof(buffer), filePtr) != NULL) {
		printf("%s", buffer);
	}

	fclose(filePtr);

	return newTable;
}

//	Add a new empty row to the table
//
void NewRow(struct Table* table) {

	//	Dynamically allocate memory for newRow
	//
	struct RowNode* newRow = malloc(sizeof(struct RowNode));
	newRow->head = NULL
	newRow->tail = NULL
	newRow->next = NULL;
	newRow->width = 0;

	//	Update table->tail
	table->tail->next = newRow;
	table->tail = newRow;
}

void FreeTable(struct Table* table) {
	struct RowNode* rowCursor = table->head;
	struct ColumnNode* columnCursor = rowCursor->head;

	while (rowCursor != NULL) {
		while (columnCursor != NULL) {
			struct ColumnNode* tmp = columnCursor;
			columnCursor = columnCursor->next;
			free(tmp);
		}
		struct RowNode* tmp = rowCursor;
		rowCursor = rowCursor->next;
		columnCursor = rowCursor->head;
		free(tmp);
	}

	free(table);
}

int main(int argc, char** argv) {

	//	Check to make sure argc matches
	//
	if (argc != 2) {
		printf("invalid. provide path to valid .csv file.\n");
		return 1;
	}

	//	Set filepath to .csv file
	//
	char* filePath = argv[1];
	

	return 0;
}
