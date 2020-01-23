#include <stdio.h>

int main(){

double sum = 0.0;
double factor = 1.0;
int infty = 6;
int sign = 1;
for (int i = 0; i <= infty; i++){
    sum += sign*(1.0/factor);
    factor *= 4.0;
    sign *= -1;
  }

printf("%f \n", sum);
return 0;
}
