#include <stdio.h>
#include <string.h>

int main(void) {
  const int NUM_ELEMENTS = 20;
  char userVals[NUM_ELEMENTS][20];
  char searchCharacter;

  int len;
  scanf("%d", &len); // first input: number of elements

  // scan in n strings to array
  for (int i = 0; i < len; i++){
    scanf("%s", userVals[i]);
  }
  
  scanf(" %c", &searchCharacter);

  for (int i = 0; i < len; i++){
    // check if character is in each string in array
    if (strchr(userVals[i], searchCharacter) != NULL){
      printf("%s\n", userVals[i]);
    }
  }
  return 0;
}