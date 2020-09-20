#include <stdio.h>

double MilesToLaps(double userMiles);

int main(void) {

  double miles;
  scanf("%lf", &miles);
  double laps = MilesToLaps(miles);
  printf("%0.2lf", laps);

  return 0;
}

double MilesToLaps(double userMiles){
  return userMiles * 4;
}