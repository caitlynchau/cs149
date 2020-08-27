#include <stdio.h>

int main(void) {
	int baseInt, headInt;
  int lines = 7;
	scanf("%d %d", &baseInt, &headInt);
   
  for (int i = 0; i < lines; i++){
    // print base
    for (int j = 0; j < 4; j++){
      if (i >= 2 && i <= 4) {
        printf("%d", baseInt);
      }else{
        printf(" ");
      }       
    }
    // print arrow
    if (i < 4){
      // print arrow head ascending
      for (int j = 0; j <= i; j++){
        printf("%d", headInt);
      }
    } else {
      // print arrow head descending
      for (int j = 0; j < 7 - i; j++){
        printf("%d", headInt);
      }
    }

    //finished printing line
    printf("\n"); 
  } // end for loop

	return 0;
}