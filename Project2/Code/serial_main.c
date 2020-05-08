#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "count_friends_of_ten.c"

#include "functions.h"


int main(int argc, char *argv[]){
/* Description
---------------
   Main program where one chooses the dimensions M and N
   of an MxN matrix, and finds the appropiate values of it.
   Writes out the number of triple friends of the matrix.
*/

// ------------------------- TEST PROGRAM ----------------------------//
  printf("\n TEST PROGRAM PART \n");

  // Test case with matrix given in the exam
  test_count_friends_of_ten();

  // ------------------------- Serialized version ----------------------------//
  printf("\n MAIN PROGRAM PART \n");

  // Time parameters
  clock_t start, end;
  double timer;

  // decide the values for M and N
  int M = 1000;
  int N = 1500;

  // allocate 2D array v and assign it with suitable values
  int **v = NULL;
  alloc2DMatrix(&v, M, N);
  construct2DMatrix(&v, M, N);
  random2DMatrix(&v, M, N);

  start = clock();
  // call function to find number of friends.
  int num_triple_friends = count_friends_of_ten(M, N, v);
  end = clock();

  timer = (double)(end - start)/CLOCKS_PER_SEC;

  printf("The time used for count_friends_of_ten is %fs \n", timer);

  printf("Number of triple friends=%d\n", num_triple_friends);

  // Deallocation of 2D array v
  free2D(v);

  return 0;

}
