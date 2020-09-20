#include <stdio.h>

int main(void) {
  int arr[20];

  // scan input
  int len;
  scanf("%d", &len);
  for (int i = 0; i < len; i++){
    scanf("%d", &arr[i]);
  }
  // scan min and max
  int min, max;
  scanf("%d %d", &min, &max);

  
  for (int i = 0; i < len; i++){
    // check if number is within range
    if (arr[i] >= min && arr[i] <= max) {
      printf("%d ", arr[i]);
    }
  }
  

  return 0;
}