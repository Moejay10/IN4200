#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "functions.h"

int count_friends_of_ten(int M, int N, int** v){
  int result = 0;
  int sum = 0;
  int horizontal = 0;
  int vertical = 0;
  int diagonal = 0;
  int triple_friends = 10;

  for (int i = 0; i < M; i++){
    for (int j = 0; j < N; j++){

      // check the sum in horizontal row.
  		if ((j - 2) >= 0) {
        result = v[i][j] + v[i][j-1] + v[i][j-2];

        if (result == triple_friends){
            horizontal++;
        }

  		}

  		// check the sum in vertical row.
  		if ((i - 2) >= 0) {
        result = v[i][j] + v[i-1][j] + v[i-2][j];

        if (result == triple_friends){
            vertical++;
        }

  		}

  		// check the sum diagonally
  		if ((i - 2) >= 0 && (j - 2) >= 0){
        result = v[i][j] + v[i-1][j-1] + v[i-2][j-2];

        if (result == triple_friends){
            diagonal++;
        }

  	   }

       // check the sum anti-diagonally
   		if ((i - 2) >= 0 && (j - 2) <= 0){
         result = v[i][j] + v[i-1][j-1] + v[i-2][j-2];

         if (result == triple_friends){
             diagonal++;
         }

   	   }


    }
  }
  sum = horizontal + vertical + diagonal;

/*
  printf("%d triple-friends of ten found horizontally \n", horizontal);
  printf("%d triple-friends of ten found vertically \n", vertical);
  printf("%d triple-friends of ten found diagonally \n", diagonal);
  printf("There are a total of %d triple-friends found in the matrix \n", sum);
*/

  return sum;
}



void test_count_friends_of_ten(){
  /* Function to test count_friends_of_ten
  using the example illustrated in the home exam. */

  // Hard coding the exact values:
  int M = 4;
  int N = 5;
  int Total_triple_friends_exact = 7;
  int v_exact[4][5] =
  {
    {1, 5, 6, 3, 1},
    {2, 4, 4, 1, 7},
    {7, 2, 3, 1, 2},
    {3, 2, 2, 5, 3},
  };

  // Provide the parameters for the function:
  int **v_test;
  int Total_triple_friends_test = 0;

  alloc2DMatrix(&v_test, M, N);

  construct2DMatrix(&v_test, M, N);

  for (int i = 0; i < M; i++){
    for (int j = 0; j < N; j++){
      v_test[i][j] = v_exact[i][j];
    }
  }

  printf("Testing count_friends_of_ten \n");

  Total_triple_friends_test = count_friends_of_ten(M, N, v_test);

  if (Total_triple_friends_test != Total_triple_friends_exact){
    printf("The total number of triple-friends of ten was extracted incorrectly in function count_friends_of_ten \n");
    printf("Total_triple_friends_exact is: %d, while the extracted Total_triple_friends_test is: %d \n", Total_triple_friends_exact, Total_triple_friends_test);
  }

  else
  {
    printf("The total number of triple-friends of ten was extracted correctly in function count_friends_of_ten \n");
    printf("Total_triple_friends_exact is: %d, while the extracted Total_triple_friends_test is: %d \n", Total_triple_friends_exact, Total_triple_friends_test);
  }


  free2D(v_test);

}
