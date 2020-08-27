#include <stdio.h>

int main(void){
	int star;
	int rows = 4; // number of rows ascending
	int spaces = rows;

	// print stars ascending
	for (int i = 0; i <= rows; i++) {
		//print spaces
		for (int j = 1; j <= spaces; j++) {
			printf(" ");
		}
		spaces--;

		//print stars
		for (int s = 1; s <= 2 * i - 1; s++) {
			printf("*");
		}
		printf("\n");
	}
	printf("  ***");
	printf("\n\n");

	printf("/\\   /\\\n");
	printf("  o o\n");
	printf(" \"   \"\n");
	printf("  ---\n");
}