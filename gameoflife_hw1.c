//GENERATE Random 0's and 1's
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
int i, N=100;
time_t t;

// Initialize the random number.
srand((unsigned) time(&t));

for(i=0; i < N; i++){
        printf("%d\n", rand() % 2);}
return(0);
}
