// 2.29

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
  double x, y, z, result;

  scanf("%lf %lf %lf", &x, &y, &z);

  // x^z
  result = pow(x, z);
  printf("%0.2lf ", result);

  // x^(y^2)
  result = pow(y, 2);
  result = pow(x, result);
  printf("%0.2lf ", result);

  // abs(y)
  result = fabs(y);
  printf("%0.2lf ", result);

  // sqrt((xy)^z)
  result = sqrt(pow(x*y, z));
  printf("%0.2lf ", result);
 
  return 0;
}
