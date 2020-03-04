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
  int Edges = 0;
  double start, end, timer;


  char **table2D;



  if (strcmp(filename, "web-NotreDame.txt") == 0 ){
    printf("File is to big for read_graph_from_file_1 \n");
  }

  else{
    // Set up time for clocking the task
    start = omp_get_wtime();

    read_graph_from_file_1(filename, &Nodes, &Edges, &table2D); // Do not use to big of a file

    end = omp_get_wtime();
    timer = end - start;

    printf("Time used for read_graph_from_file_1 is %fs \n", timer);

    //WriteMatrixtoFile(table2D, Nodes);
    //printMatrixToTerminal(table2D, Nodes);
    free2D(table2D);
  }



  int *row_ptr = NULL;
  int *col_idx = NULL;

  start = omp_get_wtime();
  read_graph_from_file_2(filename, &Nodes, &Edges, &row_ptr, &col_idx);

  end = omp_get_wtime();
  timer = end - start;

  printf("Time used for read_graph_from_file_2 is %fs \n", timer);

  if (strcmp(filename, "web-NotreDame.txt") == 0 ){
    printf("File is to big for sort_numbers_ascending \n");
  }
  else{
    start = omp_get_wtime();
    sort_numbers_ascending(row_ptr, col_idx, Edges);
    end = omp_get_wtime();

    timer = end - start;

    printf("Time used for sorting the numbers is %fs \n", timer);
  }



  //printVectorToTerminal(row_ptr, col_idx, Edges);
  //WriteVectortoFile(row_ptr, col_idx, Edges);

  free1D(col_idx);
  free1D(row_ptr);

  return 0;
}
