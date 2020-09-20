#include <stdio.h>

int main(void) {
  const int NUM_ELEMENTS = 20;
  int userVals[NUM_ELEMENTS];

  int len = 0;
  scanf("%d", &len); // first input: number of elements

  // read input 
  for (int i = 0; i < len; i++){
    scanf("%d", &userVals[i]);
  }

  int threshold = userVals[len-1]; // last value in array

  for (int i = 0; i < len; i++){
    // print out values below threshold
    if (userVals[i] < threshold) { 
      printf("%d ", userVals[i]);
    }
  }
  return 0;
}