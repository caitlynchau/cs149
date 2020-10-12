#include <stdio.h>

void SwapValues(int * userVal1, int * userVal2);

int main(void) {
    int val1, val2;
    scanf("%d %d", &val1, &val2);
    SwapValues(&val1, &val2);
    printf("%d %d\n", val1, val2);
}

void SwapValues(int * userVal1, int * userVal2) {
    int temp = *userVal1;
    *userVal1 = *userVal2;
    *userVal2 = temp;
}
