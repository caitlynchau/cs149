#include <stdio.h>
#include <limits.h>

int main(void) {
  int arr[20];

  // scan input 
  int len;
  scanf("%d", &len);
  for (int i = 0; i < len; i++){
    scanf("%d", &arr[i]);
  }
  
  int first = INT_MAX;
  int second = INT_MAX;

  for (int i = 0; i < len; i++){
    // if current is smaller than first, update both first and second
    if (arr[i] < first){
      second = first;
      first = arr[i];
    }else if (arr[i] < second && arr[i] != first){
      // update only second
      second = arr[i];
    }
  }
  
  // print first and second smallest element
  printf("%d %d\n", first, second);

  return 0;
}