#include <stdio.h>
#include <string.h>

#define SIZE 30

int main(void) {

	char str[SIZE];
	printf("Enter input string (q to quit): \n");
	fgets(str, SIZE, stdin);

	while (str[0] != 'q' && strlen(str) != 1) {

		int comma = -1;
		// find index of comma
		for (int i = 0; i < strlen(str); i++){
			if (str[i] == ',') {
				comma = i;
				break;
			}
		}

		if (comma != -1) {
			// comma found
			printf("First word: ");
			for (int i = 0; i < comma; i++){
				printf("%c", str[i]);
			}
			printf("\nSecond word: ");
			for (int i = comma + 1; i < strlen(str) - 1; i++){
				if (str[i] == ' ') continue;
				printf("%c", str[i]);
			}
			printf("\n");
		} else {
			// comma not found
			printf("Error: No comma in string.\n");
		}

		printf("Enter input string (q to quit): \n");
		fgets(str, SIZE, stdin);
	}
	
}