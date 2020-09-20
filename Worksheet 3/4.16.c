#include <stdio.h>

int main(void) {
  int input = 0;
  int count = 0, max = 0;
  int total = 0;

  scanf("%d", &input);
  // enter input until negative number is encountered
  while (input >= 0) {
    count++;
    total += input;
    if (input > max) max = input;
    scanf("%d", &input);
  }

  int avg = total / count; // calculate average
  printf("%d %d", avg, max);
}