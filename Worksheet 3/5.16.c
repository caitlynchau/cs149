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
  // print array reversed
  for (int i = len - 1; i >= 0; i--){
    printf("%d ", userVals[i]);
  }
}