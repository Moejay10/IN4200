#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "Functions.h"


int main(int argc, char* argv[]){

double result1, result2, diff;
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


// Own pow
clock_t start1 = clock();
result1 = power(N);
clock_t end1 = clock();
double tot1 = (double)(end1 - start1)/CLOCKS_PER_SEC;


// Regular pow
clock_t start2 = clock();
result2 = pow(N,100);
clock_t end2 = clock();
double tot2 = (double)(end2 - start2)/CLOCKS_PER_SEC;

diff = fabs(result1 - result2);
printf("\n The difference between pow and own function %f \n", diff);
printf("\n Own function time used = %f \n", tot1);
printf("\n pow function time used = %f \n", tot2);


return 0;
}
