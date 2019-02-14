/******************************************************************************
*  Homework1 in CS 432/632/732                           *
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
#include <time.h>

/* Function to calculate the runtime */
double gettime(void) {
  struct timeval tval;

  gettimeofday(&tval, NULL);

  return( (double)tval.tv_sec + (double)tval.tv_usec/1000000.0 );
}

/* Function to dynamically allocate memory for matrices(2D Arrays) using row major storage */
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

/*Function definition to Initialize a matrix with random 0's and 1's
       and pad them with ghost cells on all 4 sides with 0's.       */
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

/* Function to print the 2D array (used in debugging when -D flag enabled)*/
void printarray(double **a, int mrows, int ncols) {
  int i,j;

  for (i=0; i<mrows; i++) {
    for (j=0; j<ncols; j++)
      printf("%d ", (int)a[i][j]);
    printf("\n");
  }
}

/* Function to count the no. of live Neighbors */
int checkneighbors(double **a, int x, int y)
{
    int i,j;
    int count = 0;
        for(i=-1; i<2; i++){
            for(j=-1; j<2; j++){
                count = count + a[x+i][y+j];
            }
        }
    count = count - a[x][y]; //remove the cell itself from count.
    return count;
}

/* Function to create next generation of cells */
double **createNextGen(double **a, double **b, int mrows, int ncols)
{
    int i,j;

    for (i=1; i<mrows-1; i++) {
      for (j=1; j<ncols-1; j++){
        int current = a[i][j];
        int neighbors=checkneighbors(a,i,j);
            // implement rules of the game to create next gen matrix 'b'
            if(current==0 && neighbors ==3){
                b[i][j]=1;
            }
            else if(current==1 && (neighbors < 2 || neighbors>3)){
                b[i][j]=0;
            }
            else{
                b[i][j]=current;
            }
        }
        }
    return 0;
    }


/* Function to check for equality of matrices */
int ismatrixequal(double **a, double **b, int N)
{
    int i, j,flag=1;
    for (i=0; i<N; i++){
      for (j=0; j<N; j++){
          if(a[i][j]!=b[i][j]){
              /* Start by assuming matrices are equal with flag set to 1.
              If the elements are not equal then set flag to 0 and break */
              flag=0;
              break;
          }
      }
  }
  return flag;
}


int main(int argc, char **argv)
{
    int N, i;
    double **a=NULL, **b=NULL;
    double starttime, endtime;
    time_t t;

    /* Prints help message if no. of args not equal to 3 */
    if (argc != 3) {
      printf("Usage: %s <SIZE> <MAX_ITER>\n", argv[0]);
      exit(-1);
    }

    /* Args for the program - Size and Max generations. */
    N = atoi(argv[1]);
    int MAX_ITER = atoi(argv[2]);

    /* Allocate memory for matrices a,b of order N+2 to accommodate ghost cells */
    a = allocarray(N+2, N+2);
    b = allocarray(N+2, N+2);

    /* Initialize the matrix 'a' with 0's and 1's at random */
    srand((unsigned) time(&t));
    a = initarray(a, N+2, N+2);

    starttime = gettime(); //Start time to measure the working block performance

    /* Create new generations until 'MAX_ITER' iterations reached or until there's no change in generations
       Ending criteria for the game is implemented below. */
    for(i=0; i<MAX_ITER; i++){
        createNextGen(a, b, N+2, N+2);
        //printf("This is Iteration %d\n", i);


        #ifdef DEBUG_PRINT
            printf("This is Iteration %d\n", i);
            printarray(a, N+2, N+2);
            printf("\n");
            printarray(b, N+2, N+2);
            printf("\n");
        #endif

        /* Check if the matrices are equal to end the Game. */
        int test=ismatrixequal(a,b,N);

        //printf("%d\n", test);

            if(test)
            {
                printf("Exiting at iteration %d because there is no change in generations.\n", i);
                break; // stop the game basically.
            }
              else
            {
                //swapmatrices(a, b); by swapping their corresponding pointers
                double **t = a;
                a = b;
                b = t;
            }
    }

    endtime = gettime(); //End time to measure the working block performance.

    printf("Time taken = %lf seconds\n", endtime-starttime);

    return 0;
}
