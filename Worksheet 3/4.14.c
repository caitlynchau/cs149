#include <stdio.h>

int main(void) {
  int x = 0;
  scanf("%d", &x);

  while (x > 0){
    printf("%d", x % 2);
    x /= 2;
  }
}