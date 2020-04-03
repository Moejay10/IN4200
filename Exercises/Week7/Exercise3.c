# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <string.h>
# include <omp.h>


// Indexing function.
#define idx(i,j) (i*n + j)

// The following function can be used to
// compute a dense matrix-vector multiplication: x = Ay
void dense_mat_vec(int m, int n, double *x, double *A, double *y){
  int i, j;
  for (i=0; i<m; i++){
    double tmp = 0.;
    #pragma parallel for reduction(+: tmp)
    for (j=0; j<n; j++){
      tmp += A[i*n+j]*y[j];
    }
    x[i] = tmp;
  }
}

int main(int argc, char *argv[]){

  if (argc < 3)
  {
      printf("Input for size of matrix A m x n needed \n");
      exit(0);
  }

  int m = atoi(argv[1]);
  int n = atoi(argv[2]);


  double *A = malloc(m*n*sizeof *A); // m*n matrix
  double *x = (double*)malloc(m*sizeof(double));
  double *y = (double*)malloc(n*sizeof(double));

  // Assign some values
  for (size_t i = 0; i < m; i++) {
      for (size_t j = 0; j < n; j++) {
          A[idx(i,j)] = i + j;
      }
  }

  for (size_t j = 0; j < n; j++) {
      y[j] = j;
  }

  dense_mat_vec(m, n, x, A, y);

  // Print result
  if (m <= 10) {
      printf("x=\n[");
      for (size_t i = 0; i < m-1; i++) {
          printf("%.0lf, ", x[i]);
      }
      printf("%.0lf]\n", x[m-1]);
  }

  free(A);
  free(x);
  free(y);
  return 0;
}
