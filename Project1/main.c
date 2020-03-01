#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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


  read_graph_from_file_1(filename, &Nodes, &Edges);

  return 0;
}
