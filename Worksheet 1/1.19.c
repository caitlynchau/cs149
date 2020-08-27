#include <stdio.h>

int main(void){
	int userNum;

	printf("Enter integer: \n");
	scanf("%d", &userNum);

	int square = userNum * userNum;
	int cube = square * userNum;

	printf("You entered: %d\n", userNum);
	printf("%d squared is %d\n", userNum, square);
	printf("And %d cubed is %d!!\n", userNum, cube);

	int anotherNum;

	printf("Enter another integer:\n");
	scanf("%d", &anotherNum);

	int sum = userNum + anotherNum;
	int product = userNum * anotherNum;
	printf("%d + %d is %d\n", userNum, anotherNum, sum);
	printf("%d * %d is %d\n", userNum, anotherNum, product);

}