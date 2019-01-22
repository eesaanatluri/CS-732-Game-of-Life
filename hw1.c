/******************************************************************************
*  Sample C program for Homework1 in CS 432/632/732                           *
*                                                                             *
*  Program illustrate the use of dynamic memory allocation to create          *
*  contiguous 2D-matrices and use traditional array indexing.                 *
*  It also illustrate the use of gettime to measure wall clock time.          *
*                                                                             *
*  To Compile: gcc -O hw1.c (to print matrices add -D DEBUG_PRINT)            *
*  To run: ./a.out <size>                                                     *
*                                                                             *
*  Author: Eesaan Atluri                                                      *
*  Email: atlurie@uab.edu                                                     *
\******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

double gettime(void) {
  struct timeval tval;

  gettimeofday(&tval, NULL);

  return( (double)tval.tv_sec + (double)tval.tv_usec/1000000.0 );
}

double **allocarray(int P, int Q) {
  int i;
  double *p, **a;
  p = (double *)malloc(P*Q*sizeof(double));
  a = (double **)malloc(P*sizeof(double*));

  if (p == NULL || a == NULL)
    printf("Error allocating memory\n");

  /* for row major storage */
  for (i = 0; i < P; i++)
    a[i] = &p[i*Q];

  return a;
}

double **initarray(double **a, int mrows, int ncols) {
  int i,j;

  for (i=0; i<mrows; i++)
    for (j=0; j<ncols; j++){
    // Initialize the cells with random 0's and 1's
        a[i][j] = rand() % 2;
    }
  return a;
}

void printarray(double **a, int mrows, int ncols) {
  int i,j;

  for (i=0; i<mrows; i++) {
    for (j=0; j<ncols; j++)
      printf("%f ", a[i][j]);
    printf("\n");
  }
}

/* return the output array address as return value */
double **matmul1(double **a, double **b, double **c, int N)
{
    int i, j, k;
    for (i=0; i<N; i++)
      for (j=0; j<N; j++)
	for (k=0; k<N; k++)
	  c[i][j] += a[i][k]*b[k][j];
    return c;
}

/* output array address is passed as an argument */
void matmul2(double **a, double **b, double ***c, int N)
{
    int i, j, k;
    /* You could use: double **out = *c;
       and replace (*c) below with out,
       if you like to make referencing easier to understand */

    for (i=0; i<N; i++)
      for (j=0; j<N; j++)
	for (k=0; k<N; k++)
	  (*c)[i][j] += a[i][k]*b[k][j];
}

int main(int argc, char **argv)
{
    int N, i, j, k;
    double **a=NULL, **b=NULL, **c=NULL;
    double starttime, endtime;
    time_t t;

    if (argc != 2) {
      printf("Usage: %s <N>\n", argv[0]);
      exit(-1);
    }

    N = atoi(argv[1]);

    /* Allocate memory for all three matrices and temporary arrays */
    a = allocarray(N, N);
    b = allocarray(N, N);
    c = allocarray(N, N);

    /* Initialize the matrices */
    srand((unsigned) time(&t));
    a = initarray(a, N, N);
    b = initarray(b, N, N);
    c = initarray(c, N, N);

    /* Perform matrix multiplication */
    starttime = gettime();
    // c = matmul1(a,b,c,N);
    matmul2(a,b,&c,N);
    endtime = gettime();

#ifdef DEBUG_PRINT
    printarray(a, N, N);
    printf("\n");
    printarray(b, N, N);
    printf("\n");
    printarray(c, N, N);
#endif

    printf("Time taken = %lf seconds\n", endtime-starttime);

    return 0;
}
