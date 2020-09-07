// 2.25
#include <stdio.h>

int main(void) {
  int dividend, divisor;
  scanf("%d %d", &dividend, &divisor);
  for (int i = 0; i < 3; i++){
    dividend /= divisor;
    printf("%d ", dividend);
  }
  return 0;
}
