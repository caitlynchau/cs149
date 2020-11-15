#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "CommandNode.h"
#include "TraceNode.h"

/* function prototypes */
void addColumn(char ** fileArr, int rows, int columns);
void addRow(char ** fileArr, int rows, int columns);
char ** allocateFileArr(char ** fileArr, int rows, int columns);
void FreeLinkedList(CommandNode * head);

/* REALLOC calls realloc() and prints information about reallocated memory segment */
void * REALLOC(void * ptr, int size, char * file, int line)
{
	ptr = realloc(ptr, size);
	fprintf(stdout, "file=\"%s\", line=%d, function=%s, segment reallocated memory address %p to size=%d\n", 
		file, line, PRINT_TRACE(), ptr, size);
	return ptr;
}



/* MALLOC calls malloc() and prints out information about the allocated memory segment */
void * MALLOC(int size, char * file, int line)
{
	void * ptr;
	ptr = malloc(size);
	fprintf(stdout, "file=\"%s\", line=%d, function=%s, segment allocated memory address %p to size=%d\n", 
		file, line, PRINT_TRACE(), ptr, size);
	return ptr;
}



/* FREE calls free() and prints out information about the deallocated memory */
void FREE(void * ptr, char * file, int line)
{
	free(ptr);
	fprintf(stdout, "file=\"%s\", line=%d, function=%s, segment at memory address %p deallocated\n", 
		file, line, PRINT_TRACE(), ptr);

}

/* Redefine realloc, malloc, and free */
#define realloc(a,b) REALLOC(a,b,__FILE__,__LINE__)
#define malloc(a) MALLOC(a,__FILE__,__LINE__)
#define free(a) FREE(a,__FILE__,__LINE__)



int main(int argc, char * argv[]) {

	FILE * file;
	size_t bufferSize = 3;
	size_t maxLines = 10;
	char ** fileArr = NULL;
	char * line = NULL;
	int index = 0;

	/* Redirect output to memtrace.out */
    int out_fd = open("memtrace.out", O_CREAT|O_APPEND|O_RDWR, 0777);
    fprintf(stdout, "OPENED FILE\n");
    dup2(out_fd, STDOUT_FILENO);

    fprintf(stdout, "REDIRECT OUTPUT\n");


	/* Initialize linked list */
	CommandNode * head = NULL;
    CommandNode * current = NULL;
    CommandNode * prev = (CommandNode*)malloc(sizeof(CommandNode));
    fprintf(stdout, "LINKED LIST\n");

	/* Open file */
    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "proc_manager: cannot open file\n");
        exit(1);
    }

    /* Allocate space for file array */
    fileArr = allocateFileArr(fileArr, maxLines, bufferSize);
    fprintf(stdout, "FILE ARR\n");

    /* Keep reading until EOF */
    while (!feof(file)) {
    	
    	getline(&line, &bufferSize, file);
    	line[strlen(line) - 1] = '\0'; // replace newline character with null

    	/* Check if string length is too long */
		if (strlen(line) > bufferSize) {
			bufferSize = strlen(line);
			addColumn(fileArr, maxLines, bufferSize);
		}

    	/* Check if enough rows in fileArr */
    	if (index == maxLines) {
    		maxLines++;
    		addRow(fileArr, maxLines, bufferSize);
    	}

    	/* Add new line to fileArr */
    	strcpy(fileArr[index], line);

		/* Add new node to linked list */
    	current = (CommandNode*)malloc(sizeof(CommandNode));
    	CreateCommandNode(current, fileArr[index], index, NULL);
    	InsertCommandAfter(prev, current);
    	prev = current;
    	if (index == 0) head = current;


    	/* Check contents of linked list */
    	PrintNodes(head);

    	index++;

    } // end while loop

    /* Close file */
    fclose(file);

  	/* Free allocated memory */
  	free(fileArr);
  	free(line);
  	FreeLinkedList(head);

   	return 0;
}


void addColumn(char ** fileArr, int rows, int columns) {
	PUSH_TRACE("addColumn");

	fileArr = (char**)realloc(fileArr, sizeof(char*) * rows);
	for (int i = 0; i < rows; i++) {
		fileArr[i] = (char*)realloc(fileArr[i], sizeof(char) * (columns+1));
	}

	POP_TRACE();
}


void addRow(char ** fileArr, int rows, int columns) {
	PUSH_TRACE("addRow");

	fileArr = (char**)realloc(fileArr, sizeof(char*) * rows);
	for (int i = 0; i < rows; i++) {
		fileArr[i] = (char*) realloc(fileArr[i], sizeof(char) * columns);
	}

	POP_TRACE();
}

char ** allocateFileArr(char ** fileArr, int rows, int columns) {
	PUSH_TRACE("allocateFileArr");

	fileArr = (char**)malloc(sizeof(char*) * rows);
	for (int i = 0; i < rows; i++) {
		fileArr[i] = (char*)malloc(sizeof(char) * columns);
	}

	POP_TRACE();
	return fileArr;
}


// iterate through all nodes in list and free them
void FreeLinkedList(CommandNode * head) {
	PUSH_TRACE("FreeLinkedList");

	CommandNode * next = GetNextCommand(head);
	CommandNode * cur = head;

	while (cur != NULL) {

		free(cur);

		if (next == NULL) { // reached end of list
			cur = NULL;
		} else { 
		    // update next and cur
		    CommandNode * temp = next;
		    next = GetNextCommand(next);
		    cur = temp;
		}

	}

	POP_TRACE();
}