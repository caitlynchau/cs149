#include <stdio.h>
#include <string.h>

void IntegerToReverseBinary(int integerValue, char binaryValue[]);
void ReverseString(char inputString[], char reversedString[]);

int main(void) {
  int decimal = 0;
  char binary[32];
  char binaryOutput[32];

  scanf("%d", &decimal);
  IntegerToReverseBinary(decimal, binary);
  ReverseString(binary, binaryOutput);
  printf("%s", binaryOutput);
}

void IntegerToReverseBinary(int integerValue, char binaryValue[]) {
  int i = 0;
  while (integerValue > 0) {
    binaryValue[i++] = (integerValue % 2) + '0';
    integerValue /= 2;
  }
  binaryValue[i] = '\0';
}

void ReverseString(char inputString[], char reversedString[]) {
  int j = 0;
  int len = strlen(inputString);
  for (int i = len - 1; i >= 0; i--) {
    reversedString[j++] = inputString[i];
  }
}
