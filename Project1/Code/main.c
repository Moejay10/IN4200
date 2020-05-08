#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "read_graph_from_file1.c"
#include "read_graph_from_file2.c"

#include "count_mutual_links1.c"
#include "count_mutual_links2.c"

#include "top_n_webpages.c"

#include "functions.h"


int main(int argc, char *argv[]){


  if (argc < 2){

        printf("Filename required.\n");
        exit(0);
  }

  char* filename = argv[1];

  clock_t start, end;
  double timer[6];
  for (int i = 0; i < 6; i++){
    timer[i] = 0;
  }

  int runs = 10; // Number of time running the program to find the average time


// ------------------------- TEST PROGRAM ----------------------------//

  printf("\n TEST PROGRAM PART \n");

  test_read_graph_from_file1();
  test_read_graph_from_file2();
  printf("\n");

  test_count_mutual_links1();
  test_count_mutual_links2();
  printf("\n");

  test_top_n_webpages(8);

  printf("\n");
  printf("\n");

  // ------------------------- MAIN PROGRAM ----------------------------//
  printf("\n MAIN PROGRAM PART \n");
  printf("\n");


  // ------------------------- Serialized version ----------------------------//
  printf("Serialized version of the code running \n \n");

  for (int i = 0; i < runs; i++){

    // Defining variables
    int Nodes = 0;
    int Nodes1 = 0;
    int N_links1 = 0;
    int n = 8;

    char **table2D;

    int *row_ptr = NULL;
    int *col_idx = NULL;

    // Data in table format

    if (strcmp(filename, "web-NotreDame.txt") == 0 )
    {
      printf("File is to big for read_graph_from_file_1 \n");
    }

    else{
          // Set up average time for clocking the task
          start = clock();
          read_graph_from_file1(filename, &Nodes, &table2D); // Do not use to big of a file
          end = clock();
          timer[0] += (double)(end - start)/CLOCKS_PER_SEC;

          if (i == runs - 1){
            timer[0] /= runs;
            printf("The average time used for read_graph_from_file_1 is %fs \n", timer[0]);
          }


          int Total_involvements1;
          int *num_involvements1 = (int*)malloc(Nodes*sizeof(int));

          start = clock();
          Total_involvements1 = count_mutual_links1(Nodes, table2D, num_involvements1);
          end = clock();
          timer[1] += (double)(end - start)/CLOCKS_PER_SEC;

          if (i == runs - 1){
            timer[1] /= runs;
            printf("The average time used for count_mutual_links1 is %fs \n", timer[1]);

            printf("Total number of mutual web linkage are %d \n", Total_involvements1);
          }



          start = clock();
          top_n_webpages(Nodes, num_involvements1, n);
          end = clock();
          timer[2] += (double)(end - start)/CLOCKS_PER_SEC;

          if (i == runs - 1){
            timer[2] /= runs;
            printf("The average time used for top_n_webpages is %fs \n", timer[2]);
          }

          free(num_involvements1);
          free2D(table2D);
      }


      printf("\n");

      // Data in CRS format
      start = clock();
      read_graph_from_file2(filename, &Nodes1, &N_links1, &row_ptr, &col_idx);
      end = clock();
      timer[3] += (double)(end - start)/CLOCKS_PER_SEC;

      if (i == runs - 1){
        timer[3] /= runs;
        printf("The average time used for read_graph_from_file_2 is %fs \n", timer[3]);
      }

      int Total_involvements2;
      int *num_involvements2 = (int*)malloc(Nodes1*sizeof(int));

      start = clock();
      Total_involvements2 = count_mutual_links2(Nodes1, N_links1, row_ptr, col_idx, num_involvements2);
      end = clock();
      timer[4] += (double)(end - start)/CLOCKS_PER_SEC;

      if (i == runs - 1){
        timer[4] /= runs;
        printf("The average time used for count_mutual_links2 is %fs \n", timer[4]);
        printf("Total number of mutual web linkage are %d \n", Total_involvements2);
      }


      start = clock();
      top_n_webpages(Nodes1, num_involvements2, n);
      end = clock();
      timer[5] += (double)(end - start)/CLOCKS_PER_SEC;

      if (i == runs - 1){
        timer[5] /= runs;
        printf("The average time used for top_n_webpages is %fs \n", timer[5]);
        WriteVectortoFile(timer, 6, 0);
      }

      free(num_involvements2);
      free(row_ptr);
      free(col_idx);
    }




  return 0;
}
