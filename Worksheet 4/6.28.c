#include <stdio.h>

int LargestNumber(int userNum1, int userNum2, int userNum3);
int SmallestNumber(int userNum1, int userNum2, int userNum3);

int main(void) {

  int num1, num2, num3;
  scanf("%d %d %d", &num1, &num2, &num3);

  printf("largest: %d\n", LargestNumber(num1, num2, num3));
  printf("smallest: %d\n", SmallestNumber(num1, num2, num3));
  
  return 0;
}

int LargestNumber(int userNum1, int userNum2, int userNum3){
  int largest = userNum1;
  if (userNum2 > largest) {
    largest = userNum2;
  }
  if (userNum3 > largest) {
    largest = userNum3;
  }
  return largest;
}

int SmallestNumber(int userNum1, int userNum2, int userNum3){
  int smallest = userNum1;
  if (userNum2 < smallest){
    smallest = userNum2;
  }
  if (userNum3 < smallest){
    smallest = userNum3;
  }
  return smallest;
}
