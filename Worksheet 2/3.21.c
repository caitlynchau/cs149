// 3.21

#include <stdio.h>

int main(void) {
  int arr[3];
  for (int i = 0; i < 3; i++){
    scanf("%d", &arr[i]);
  }
  
  int smallest = arr[0];
  for (int i = 1; i < 3; i++){
    if (arr[i] < smallest){
      smallest = arr[i];
    }
  }
  printf("%d", smallest);
}