# include <stdlib.h>
# include <time.h>
# include <stdio.h>
# include <math.h>
# include <string.h>
# include <omp.h>


int main(int argc, char *argv[]){

  if (argc < 4)
  {
      printf("Input for which openmp schedule_type and chunk size and vector size needed\n");
      exit(0);
  }

  int Task = atoi(argv[1]);
  int chunk_size = atoi(argv[2]);
  int N = atoi(argv[3]);


  double *a = (double*)malloc(N*sizeof(double));
  double *b = (double*)malloc(N*sizeof(double));

  double sum = 0;
  double exact = 0;

  double start, end;

  for (int i = 0; i < N; i++){
    a[i] = 2*i + 1;
    b[i] = 2*i;
    exact += (2*i)*(2*i + 1);
  }

  printf("Exact dot product between the vectors = %g \n", exact);


  if (Task == 1)
  {
    start = omp_get_wtime();
    #pragma omp parallel for schedule(static, chunk_size) reduction(+: sum)
    for (int i = 0; i < N; i++){
      sum += a[i] * b[i];
    }
    end = omp_get_wtime();
    printf("Calculated dot product between the vectors = %g \n", sum);
    printf("Time used is %fs \n", end - start);
  }

  if (Task == 2)
  {
    start = omp_get_wtime();
    #pragma omp parallel for schedule(dynamic, chunk_size) reduction(+: sum)
    for (int i = 0; i < N; i++){
      sum += a[i] * b[i];
    }
    end = omp_get_wtime();
    printf("Calculated dot product between the vectors = %g \n", sum);
    printf("Time used is %fs \n", end - start);
  }

  if (Task == 3)
  {
    start = omp_get_wtime();
    #pragma omp parallel for schedule(runtime) reduction(+: sum)
    for (int i = 0; i < N; i++){
      sum += a[i] * b[i];
    }
    end = omp_get_wtime();
    printf("Calculated dot product between the vectors = %g \n", sum);
    printf("Time used is %fs \n", end - start);
  }

  free(a);
  free(b);

  return 0;
}
