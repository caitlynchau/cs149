#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CommandNode.h"



int main(int argc, char * argv[]) {

	FILE * file;
	size_t bufferSize = 50;
	size_t maxLines = 10;
	char ** fileArr;
	int index = 0;

	/* Initialize linked list */
	CommandNode * head = NULL;
    CommandNode * current = NULL;
    CommandNode * prev = (CommandNode*)malloc(sizeof(CommandNode));


    /* Allocate space for file array */
    fileArr = (char**)malloc(maxLines * sizeof(char*));

	/* Open file */
    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "proc_manager: cannot open file\n");
        exit(1);
    }

    /* Keep reading until EOF */
    while (!feof(file)) {
    	char * line = (char*)malloc(bufferSize);
    	getline(&line, &bufferSize, file);
    	line[strlen(line) - 1] = '\0'; // replace newline character with null


    	/* Add new node to linked list */
    	current = (CommandNode*)malloc(sizeof(CommandNode));
    	CreateCommandNode(current, line, index, NULL);
    	InsertCommandAfter(prev, current);
    	prev = current;
    	if (index == 0) head = current;

    	/* Check if enough space in fileArr (realloc) */
    	if (index == maxLines) {
    		maxLines *= 2;
    		fileArr = realloc(fileArr, maxLines * sizeof(char*));
    	}

    	/* Add new line to fileArr */
    	fileArr[index++] = line;

    } // end while loop

    fclose(file);

    // for (int i = 0; i < index; i++) {
    // 	printf("%s\n", fileArr[i]);
    // }

    current = head;
    while (current != NULL) {
    	printf("%s\n", current->command);
    	current = GetNextCommand(current);
    }


    
}