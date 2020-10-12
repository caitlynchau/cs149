#include <stdio.h>
#include <string.h>

/* function prototype */
int CountCharacters(char userChar, char* userString);


int main(void) {
	char target;
	char userString[50];
  // get user input
	scanf("%c", &target);
	fgets(userString, 50, stdin);
  // count character occurances 
	int count = CountCharacters(target, userString);
  printf("%d\n", count);

	return 0;
}

int CountCharacters(char userChar, char* userString) {
	int count = 0;

	for (int i = 0; i < strlen(userString); i++){
		if (userString[i] == userChar) count++; // increment count if match
	}
	return count;
}