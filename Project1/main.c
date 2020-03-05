#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <omp.h> // OpenMP

#include "functions.h"


int main(int argc, char *argv[]){

  if (argc < 2){

        printf("Filename required.\n");
        exit(0);
  }
  char* filename = argv[1];

  int Nodes = 0;
  int N_links = 0;
  double start, end, timer;


  char **table2D;



  if (strcmp(filename, "web-NotreDame.txt") == 0 ){
    printf("File is to big for read_graph_from_file_1 \n");
  }

  else{
    // Set up time for clocking the task
    start = omp_get_wtime();

    read_graph_from_file_1(filename, &Nodes, &table2D); // Do not use to big of a file

    end = omp_get_wtime();
    timer = end - start;

    printf("Time used for read_graph_from_file_1 is %fs \n", timer);

    int Total_involvements;
    int *num_involvements = (int*)malloc(Nodes*sizeof(int));
    Total_involvements = count_mutual_links1(Nodes, table2D, num_involvements);


    printf("Total number of mutual web linkage are %d \n", Total_involvements);

    if (strcmp(filename, "100nodes_graph.txt") == 0 ){
      printf("table2D is too big to print out \n");
    }

    else{
      printMatrixToTerminal(table2D, Nodes);
      WriteMatrixtoFile(table2D, Nodes);

      printf("Number of involvements per webpage is \n");
      printVectorToTerminal(num_involvements, Nodes);
    }



    free(num_involvements);
    free2D(table2D);
  }



  int *row_ptr = NULL;
  int *col_idx = NULL;

  start = omp_get_wtime();
  read_graph_from_file_2(filename, &Nodes, &N_links, &row_ptr, &col_idx);

  end = omp_get_wtime();
  timer = end - start;

  printf("Time used for read_graph_from_file_2 is %fs \n", timer);
  int N_rows = Nodes + 1;


  //printVectorToTerminal2(row_ptr, col_idx, N_rows, N_links);
  //WriteVectortoFile2(row_ptr, col_idx, N_rows, N_links);

  free1D(col_idx);
  free1D(row_ptr);

  return 0;
}
