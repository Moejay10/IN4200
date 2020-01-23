#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[]){

// Checking if number of argument is
    // equal to 4 or not.
if (argc < 2){
printf("\n enter 2 arguments only eg.\"filename arg1 !!\" \n");
return EXIT_FAILURE;
    }

int dim;
dim = atoi(argv[1]);

double *array = malloc(dim*sizeof(double));

for (int i = 0; i < dim; i++){
array[i] = rand();
  }
double min, max;
min = max = array[0];

for (int i = 1; i < dim; i ++){
if (min > array[i]){
  min = array[i];
    }
if (max < array[i]){
    max = array[i];
    }

  }
printf("\n Dimension: %d", dim);
printf("\n Minimum: %f", min);
printf("\n Maximum: %f", max);
printf("\n");

free(array);
return 0;
}
