#include "Functions.h"



double numerical_integration (double x_min, double x_max, int N){

double h = (x_max-x_min)/(double)(N);
double x, sum = 0.0;
double temp;

  for (int i = 0; i < N; i++){
    x = x_min + (i+0.5)*h;
    temp = 1.0+x*x;
    sum = sum + 4.0/temp;
  }

return sum*h;
}
