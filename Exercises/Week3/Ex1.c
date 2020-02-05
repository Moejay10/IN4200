#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Functions.h"


int main(int argc, char* argv[]){

double pi = 4*atan(1);
double a, b, result;
a = 0;
b = 1;
int N;

// Checking if number of argument is
    // equal to 1 or not.
    if (argc < 2 || argc > 3)
    {
        printf("Enter 2 arguments only eg.filename N!! \n");
        return 0;
    }

    // Converting string type to integer type
    // using function "atoi( argument)"
    //a = atoi(argv[1]);
    //b = atoi(argv[2]);
    N = atoi(argv[1]);

    // Checking if all the numbers are positive of not
    if (N < 0){
        printf("Enter only positive values in arguments !!");
        return 1;
    }


result = numerical_integration(a,b,N);
double diff = fabs(result - pi);
printf("\n Analytical = %f", pi);
printf("\n Numerical = %f", result);
printf("\n Difference = %f \n", diff);

return 0;
}
