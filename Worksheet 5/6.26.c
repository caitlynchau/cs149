#include <stdio.h>
#include <string.h>

#define LEN 50

void printReverse(char * str);

int main(void) {
	char buffer[LEN];
	fgets(buffer, LEN, stdin);

	while (strcmp(buffer, "quit\n") != 0 
		&& strcmp(buffer, "Quit\n") != 0 
		&& strcmp(buffer, "q\n") != 0) {
		printReverse(buffer);
		fgets(buffer, LEN, stdin);
	}

	return 0;
}

void printReverse(char * str) {
	int len = strlen(str);
	for (int i = len - 2; i >= 0; i--) {
		printf("%c", str[i]);
	}
	printf("\n");
}