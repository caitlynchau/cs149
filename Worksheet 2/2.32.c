// 2.32
#include <stdio.h>

int main(void) {
  int currentPrice, lastMonthsPrice;

  scanf("%d %d", &currentPrice, &lastMonthsPrice);

  int change = currentPrice - lastMonthsPrice;

  printf("This house is $%d. ", currentPrice);
  printf("The change is $%d since last month.\n", change);

  printf("The estimated monthly mortage is $%lf.", (currentPrice * 0.051) / 12);
 
  return 0;
}