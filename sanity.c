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
#include <stdbool.h>

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
        a[0][j] = 0;
        a[i][0] = 0;
        a[mrows-1][j] = 0;
        a[i][ncols-1] = 0;
    }
  return a;
}

void printarray(double **a, int mrows, int ncols) {
  int i,j;

  for (i=0; i<mrows; i++) {
    for (j=0; j<ncols; j++)
      printf("%d ", (int)a[i][j]);
    printf("\n");
  }
}

bool ismatrixequal(double **a, double **b, int N)
{
    int i, j, flag=1;
    for (i=0; i<N; i++){
      for (j=0; j<N; j++){
          printf("checking a%d,%d\n",i,j);
          if(a[i][j]!=b[i][j]){
              printf("%d,%d\t",i,j);
              /* Using ! condition will allow you to not having check for equality for all elements.
              It will bail out on first inequality. Using this for my sanity. */
              flag=0;
              break;
          }

      }

  } return flag;
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
    //int MAX_ITER = atoi(argv[2]);

    /* Allocate memory for matrices a,b and temporary arrays */
    a = allocarray(N+2, N+2);
    b = allocarray(N+2, N+2);
    //c = allocarray(N+2, N+2);

    starttime = gettime();
    /* Initialize the matrix 'a' with 0's and 1's at random */
    srand((unsigned) time(&t));
    a = initarray(a, N+2, N+2);
    b = initarray(b, N+2, N+2);

    //for(i=0; i<MAX_ITER; i++){
        #ifdef DEBUG_PRINT
            printarray(a, N+2, N+2);
            printf("\n");
            printarray(b, N+2, N+2);
            printf("\n");
            //printarray(c, N+2, N+2);
        #endif
        //Check if the matrices are equal to end the Game.
        bool test=ismatrixequal(a,b,N+2);
printf("%s\n", test ? "true" : "false");
            if(test)
            {
                printf("Both gens are equality.\n");
                //break; // stop the game basically.
            }
              else
            {
                double **t = a;
                a = b;
                b = t;
                #ifdef DEBUG_PRINT
                    printarray(a, N+2, N+2);
                    printf("\n");
                    printarray(b, N+2, N+2);
                    //printarray(c, N+2, N+2);
                #endif
            }

    //}


    endtime = gettime();


    printf("Time taken = %lf seconds\n", endtime-starttime);

    return 0;
}
