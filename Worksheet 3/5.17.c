#include <stdio.h>

int main(void) {
  const int NUM_ELEMENTS = 20;
  int userVals[NUM_ELEMENTS];
  int i = 0, input = 0;
  
  // enter user input until negative number encountered
  scanf("%d", &input); 
  while (input > 0){
    userVals[i++] = input;
    scanf("%d", &input);
  }
  // print middle element
  printf("%d", userVals[i/2]);
  return 0;
}