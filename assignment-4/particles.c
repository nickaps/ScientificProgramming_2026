
//
//	particles.c is a program that will collect
//	various particle types into a .csv file before
//	reading it into structures and effectively
//	freeing the memory on closure.
//
//	Created by Nick Chapman, 11-7-2026
//
//
//
//                             |  Grade Received   |
//                             |      | ___%|      |
#define __FINAL_MARK                    "??"
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//	Cross Platform Screen Clear
//
//		ANSI escape sequences are possibly a better
//		universal option, but I think that using
//		macros is fun and looks boujee :P
//
#if defined(_WIN32) || defined(_WIN64)
	#define __CLEAR_SCREEN system("cls")
	#define __SHOW_DIR system("dir")
#else
	#define __CLEAR_SCREEN system("clear")
	#define __SHOW_DIR system("ls -l")
#endif
//

//	Structure Definition & Implementation
//
typedef struct Particle Particle;
typedef struct ListNode ListNode;
//	
//	Particle Struct contains
//		- Name
//		- Mass (in MeV/c^2)
//		- Charge (measured in thirds of the magnitude of an electron)
//		- Spin (measured in increments of halves to include all particles)
//		
struct Particle {
	char name[30];
	double mass;
	int thirdCharge;
	int halfSpin; 
};
//
//	List Node contains
//		- Particle Data Struct Pointer
//		- ListNode Pointer to the next node in series
//
struct ListNode {
	Particle* dataLink;
	ListNode* next;
};
//

// Globals
//
int running = 0;
char currentTable[64];
FILE* fptr = NULL;
ListNode* list = NULL;
//

//	Function Prototypes
//
Particle* PromptForParticle();
ListNode* GetEndOfList(ListNode** list);
void AddNode(ListNode** listPtr, Particle* data);
void FreeList(ListNode** list);
void DisplayList(ListNode** list);
int OpenList(char* fname);
int CloseList();
int SaveList(char* fname);
int DeleteList();
void PushPrompt();
void Pop();
void Pick(int index);
//
void _CLI_PROMPT(char* buffer, size_t bufferSize);
void _PARTICLE_CLI();
void _DISPLAY_HELP();
void _WELCOME_SCREEN();
void _PROJECT_SUMMARY();
void _INTERPRET_COMMAND(char* cmd);
//

//	Function Implementations
//
Particle* PromptForParticle() {

	Particle* newParticle = malloc(sizeof(Particle));

	printf("Enter following information:\n");
	printf("\tNAME: ");
	char buffer[sizeof(newParticle->name)];
	if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
		char* c = buffer;
		while (*c != '\0' && *c != '\n')
			c++;
		*c = '\0';
		strncpy(newParticle->name, buffer, sizeof(newParticle->name));
	}
	memset(buffer, 0, sizeof(buffer));
	printf("\tMASS: ");
	if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
		newParticle->mass = atof(buffer);
	}
	memset(buffer, 0, sizeof(buffer));
	printf("\tCHARGE: ");
	if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
		newParticle->thirdCharge = atoi(buffer);
	}
	memset(buffer, 0, sizeof(buffer));
	printf("\tSPIN: ");
	if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
		newParticle->halfSpin = atoi(buffer);
	}

	return newParticle;
}
//
void AddNode(ListNode** listPtr, Particle* data) {
	if (listPtr == NULL) return;
	ListNode* ptr = *listPtr;
	if (ptr == NULL) {
		ptr = malloc(sizeof(ListNode));
		*listPtr = ptr;
	}
	else {
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = malloc(sizeof(ListNode));
		ptr = ptr->next;
	}
	ptr->dataLink = data;
	ptr->next = NULL;
}
//
void FreeList(ListNode** list) {
	ListNode* ptr = *list;
	if (ptr == NULL) {
		return;
	}
	ListNode* temp = ptr;
	while (ptr != NULL) {
		temp = ptr;
		ptr = ptr->next;
		free(temp->dataLink);
		free(temp);
	}
	*list = NULL;
}
//
void DisplayList(ListNode** list) {
	ListNode* ptr = *list;
	if (fptr == NULL) {
		printf("invalid. no table currently opened.\n");
		return;
	}
	if (ptr == NULL) {
		printf("Empty table.\n");
		return;
	}
	printf("\t%5s || \t%15s | %22s     | %9s | %9s |\n", "INDEX", "NAME", "MASS (MeV/c^2)", "CHARGE", "SPIN");
	int i = 0;
	while (ptr != NULL) {
		Particle* p = ptr->dataLink;
		printf("\t%5d || \t%15s | ~%15.5f (MeV/c^2) | %9f | %9f |\n", i, p->name, p->mass, (double)(p->thirdCharge)/3.0, (double)(p->halfSpin)/2.0);
		ptr = ptr->next;
		i++;
	}
}
//
ListNode* GetEndOfList(ListNode** list) {
	ListNode* ptr = *list;
	if (ptr == NULL) return NULL;
	while (ptr->next != NULL)
		ptr = ptr->next;
	return ptr;
}
//
int OpenList(char* fname) {
	if (strcmp(currentTable, "") != 0) {
		printf("invalid. cannot open another file when one is already opened.\n");
		return 1;
	}

	char fpath[100] = {0};
	snprintf(fpath, sizeof(fpath), "./%s.csv", fname);
	fptr = fopen(fpath, "r+");

	if (fptr == NULL) {
		printf("failed to open file.\n");
		return 1;
	}
	strcpy(currentTable, fname);

	char buffer[100] = {0};
	while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
		Particle* particle = malloc(sizeof(Particle));
		int index = 0;
		char *token = strtok(buffer, ", ");
		while (token != NULL) {
			switch (index) {
				case 0:
					//	Name property
					//
					strcpy(particle->name, token);
					break;
				case 1:
					//	Mass property (MeV)
					//
					particle->mass = atof(token);
					break;
				case 2:
					//	Charge property (thirds of magnitude of (e-)
					//
					particle->thirdCharge = atoi(token);
					break;
				case 3:
					//	Spin property (halves)
					//
					particle->halfSpin = atoi(token);
					break;
			}
			index++;
			token = strtok(NULL, ", ");
		}
		AddNode(&list, particle);
	}
	
	return 0;
}
//
int CreateList(char* fname) {
	char fpath[100];
	snprintf(fpath, sizeof(fpath), "./%s.csv", fname);

	fptr = fopen(fpath, "w");

	if (fptr == NULL) {
		printf("failed to create file.\n");
		return 1;
	}
	
	fclose(fptr);
	fptr = NULL;

	return 0;
}
//
int CloseList() {
	if (fptr == NULL) {
		printf("invalid. no file currently open.\n");
		return 1;
	}
	
	fclose(fptr);
	fptr = NULL;

	memset(currentTable, 0, sizeof(currentTable));

	FreeList(&list);
	
	return 0;
}
//
int SaveList(char* fname) {

	if (fptr == NULL) {
		printf("invalid. no file currently open.\n");
		return 1;
	}

	if (list == NULL) {
		printf("Empty table.\n");
		return 1;
	}
	
	char fpath[100];
	if (strcmp(fname, "") == 0) {
		snprintf(fpath, sizeof(fpath), "./%s.csv", currentTable);
	}
	else {
		snprintf(fpath, sizeof(fpath), "./%s.csv", fname);
	}

	fclose(fptr);
	fptr = fopen(fpath, "w");
	if (fptr == NULL) {
		printf("failed to open file.\n");
		return 1;
	}
	
	ListNode* ptr = list;
	
	while (ptr != NULL) {
		Particle* d = ptr->dataLink;
		fprintf(fptr, "%s,%f,%d,%d\n", d->name, d->mass, d->thirdCharge, d->halfSpin);
		ptr = ptr->next;
	}

	fclose(fptr);
	fptr = fopen(fpath, "r+");

	return 0;
}

int DeleteList() {
	if (fptr == NULL) {
		printf("invalid. no file currently opened.\n");
		return 1;
	}

	printf("are you sure you want to delete \"%s\"? (Y/n) ", currentTable);
	
	char answer[5];
	if (fgets(answer, sizeof(answer), stdin)) {
		char tok = tolower(answer[0]);
		answer[0] = tok;
	}
	if (answer[0] != 'y') {
		return 0;
	}
	
	char fpath[100];
	snprintf(fpath, sizeof(fpath), "./%s.csv", currentTable);
	
	if (remove(fpath) == 0) {
		printf("successfully deleted table.\n");
	}
	else {
		printf("failed to remove table at \"%s\"\n", currentTable);
	}

	CloseList(&list);

	return 0;
}
//
void PushPrompt() {
	Particle* data = PromptForParticle();
	AddNode(&list, data);
}
//
void Pop() {
	if (list == NULL) {
		printf("Empty table.\n");
	}

	ListNode* ptr = list;
	while (ptr->next->next != NULL) {
		ptr = ptr->next;
	}
	ListNode* tmp = ptr->next;
	free(tmp->dataLink);
	free(tmp);
	ptr->next = NULL;
}
//
void Pick(int index) {
	int i = 0;
	ListNode* ptr = list;
	while (ptr != NULL && i < index - 1) {
		ptr = ptr->next;
	}
	ListNode* tmp = ptr->next;
	ptr->next = tmp->next;
	
	free(tmp->dataLink);
	free(tmp);
}
//
void _WELCOME_SCREEN() {
	__CLEAR_SCREEN;
		
	printf("Welcome to the Particle Interface\n");
	printf("type help for help and exit to quit\n");
	printf("Created by Nick Chapman, 11-7-2026\n");
	printf("\n");
}
//
void _PROJECT_SUMMARY() {

	printf("\n");
	printf("\t\tSelf-Assessment of Assignment 4\n");
	printf("\n");
	
	printf("\tIf this were a perfect project, I would include some more operations to\n");
	printf("\tthe toolbox such as insert to insert Particles between others in the list,\n");
	printf("\tstitch to stitch one table to the end of another, and splice to insert an\n");
	printf("\tentire table in the middle of another. I think that I should have began this\n");
	printf("\tproject earlier as I continued to procrastinate until it was already too late.\n");
	printf("\tFunctionally I believe this program is admissable, but it could be expanded upon.\n");
	printf("\tMore than just adding new tools: I would like to allow the user to make tables\n");
	printf("\tof any type that use a 0 line header to read what the property name is and what\n");
	printf("\tthe data-type is. For instance, this could be one of many different kinds of\n");
	printf("\ttables that has a header like:\n");
	printf("\t\t\"Name:str,Mass:double,Charge:int,Spin:int\"\n");

	printf("\n");
	printf("\tI also think it would be cool if I added a gen command which would create\n");
	printf("\ta csv file with hardcoded information for the standard model. Another thing\n");
	printf("\tthat always comes to mind is the way I work with charges and spins in this.\n");
	printf("\tI think I should have made a way to work with fractions so that you can enter\n");
	printf("\tthem like \"1/2\" or \"2/3\" and it would parse them into either num/dem in\n");
	printf("\tthe file, or as a double that represents them in the file.\n");
	printf("\tIt would look a lot better and be more intuitive if I used fractions for inputting\n");
	printf("\tand displaying the charge and spin.\n");

	printf("\t\t[RECEIVED: %s / 100]\n", __FINAL_MARK);
}
//
void _DISPLAY_HELP() {

	printf("\n\tThe following commands are used to view, update and delete");
	printf("\n\tvarious tables of information about various particles.");
	printf("\n\tWhen adding values to your table remember that--in order to");
	printf("\n\taccommodate all standard model particles--charge will be entered");
	printf("\n\tin thirds of the magnitude of charge of an electron, and");
	printf("\n\tspin will be entered in half intervals. Mass is simply entered as a");
	printf("\n\tdouble in units of MeV/c^2.");
	printf("\n\tCharge:  -3 = -1(e-), 2 = 2/3(e-)\tSpin:  1 = 1/2, 4 = 4/2 = 2");
	
	printf("\n");

	printf("\n\texit   - close the program. will automatically close any file");
	printf("\n\thelp   - you seem to have figured this one out :D");
	printf("\n\tclear  - clear the screen");
	printf("\n\tls     - list contents of current working directory");
	printf("\n\tnew    - create a new table as a .csv file");
	printf("\n\topen   - open existing table to view or edit");
	printf("\n\tclose  - close the currently opened table");
	printf("\n\tview   - view the currently opened table");
	printf("\n\tpush   - place a Particle onto the end of the openend table");
	printf("\n\tpop    - remove the Particle from the end of the opened table");
	printf("\n\tpick   - remove the Particle from a specific index in opened table");
	printf("\n\tdelete - delete a table file permanently");

	printf("\n");
	printf("\n\ttype: project-summary for a description of things I would add or change if I further work on this project.\n");

	printf("\n");
}
//
void _CLI_PROMPT(char* buffer, size_t bufferSize) {
	printf("%s> ", currentTable);
	if (fgets(buffer, bufferSize, stdin)) {
		if (strcmp(buffer, "") != 0)
			_INTERPRET_COMMAND(buffer);
	}
}
//
void _INTERPRET_COMMAND(char* cmd) {

	if (strcmp(cmd, "\n") == 0) return;

	#define _MAX_ARGS 10
	
	int argc = 0;
	char* args[_MAX_ARGS] = {0};
	char* token = strtok(cmd, " ");

	while (token != NULL && argc < _MAX_ARGS) {
		args[argc] = token;
		token = strtok(NULL, " \n");
		argc++;
	}

	char* c = args[argc - 1];
	while(*c != '\0' && *c != '\n')
		c++;
	*c = '\0';

	//
	//	Built-Ins
	//	(All commands currently available)
	//
	if (strcmp(args[0], "exit") == 0) {
		running = 1;
		return;
	}
	if (strcmp(args[0], "help") == 0) {
		_DISPLAY_HELP();
		return;
	}
	if (strcmp(args[0], "clear") == 0) {
		__CLEAR_SCREEN;
		return;
	}
	if (strcmp(args[0], "ls") == 0) {
		__SHOW_DIR;
		return;
	}
	if (strcmp(args[0], "new") == 0) {
		if (argc != 2) {
			printf("invalid. usage: new <FILE-NAME>\n");
			return;
		}
		CreateList(args[1]);
		return;
	}
	if (strcmp(args[0], "open") == 0) {
		if (argc != 2) {
			printf("invalid. usage: open <FILE-NAME>\n");
			return;
		}
		OpenList(args[1]);
		return;
	}
	if (strcmp(args[0], "close") == 0) {
		if (argc != 1) {
			printf("inavlid. usage: close\n");
			return;
		}
		CloseList();
		return;
	}
	if (strcmp(args[0], "view") == 0) {
		if (argc != 1) {
			printf("invalid. usage: view\n");
			return;
		}
		DisplayList(&list);
		return;
	}
	if (strcmp(args[0], "push") == 0) {
		if (argc != 1) {
			printf("invalid. usage: push\n");
			return;
		}
		PushPrompt();
		return;
	}
	if (strcmp(args[0], "pop") == 0) {
		if (argc != 1) {
			printf("invalid. usage: pop\n");
			return;
		}
		Pop();
		return;
	}
	if (strcmp(args[0], "pick") == 0) {
		if (argc != 2) {
			printf("invalid. usage: pick <INDEX>\n");
			return;
		}
		Pick(atoi(args[1]));
		return;
	}
	if (strcmp(args[0], "save") == 0) {
		if (argc > 2) {
			printf("invalid. usage: save [SAVE-AS-DIR]\n");
			return;
		}
		if (argc == 1) {
			SaveList("");
		}
		else if (argc == 2) {
			SaveList(args[1]);
		}
		return;
	}
	if (strcmp(args[0], "delete") == 0) {
		if (argc != 1) {
			printf("invalid. usage: delete\n");
			return;
		}
		DeleteList();
		return;
	}
	if (strcmp(args[0], "project-summary") == 0) {
		if (argc != 1) {
			printf("invalid. usage: project-summary");
			return;
		}
		_PROJECT_SUMMARY();
		return;
	}

	printf("\"%s\" is not a known command.\n", args[0]);
}
//
//	_PARTICLE_CLI() is a method that will loop
//	input from the user in order to load sets,
//	save sets, add to and remove from sets.
//
void _PARTICLE_CLI() {

	ListNode* list = NULL;

	char buffer[256] = {0};

	_WELCOME_SCREEN();

	while (running == 0) {

		_CLI_PROMPT(buffer, sizeof(buffer));

		//	Clear Buffer
		//
		memset(buffer, 0, sizeof(buffer));
	}

	FreeList(&list);

	if (fptr != NULL) {
		fclose(fptr);
	}
}
//

//	Entry Point
//
int main(void) {

	//	Program loops within the _PARTICLE_CLI() method.
	//	Simply reads command, interprets it, and prompts for the next.
	//
	_PARTICLE_CLI();

}
