#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "count_friends_of_ten.c"

#include "functions.h"


int main(int argc, char *argv[]){

/*
  if (argc < 2){

        printf("Filename required.\n");
        exit(0);
  }
*/

  //test_count_friends_of_ten();

  int M = 100;
  int N = 150;
  int **v = NULL;

  alloc2DMatrix(&v, M, N);
  construct2DMatrix(&v, M, N);

  random2DMatrix(&v, M, N);

  int num_triple_friends = count_friends_of_ten(M, N, v);

  printf("Number of triple friends=%d\n", num_triple_friends);

  // Deallocation of 2D array v
  free2D(v);

  return 0;

}
