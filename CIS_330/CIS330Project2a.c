
/*
 * Compile this program as: gcc example.c # assuming you named it example.c
 * Run this program as:     ./a.out
 */ 
 
#include <stdio.h>   /* need this include for printf */
#include <stdlib.h>  /* need this include for malloc */
 
int main()
{
    int *A = malloc(sizeof(int)*21);  /* we are allocating 21 ints */
    
    /* Note that the values in the table are the Fibonacci sequence */
    A[0] = 0;
    A[1] = 1;
    for (int i = 2 ; i < 21 ; i++)
       A[i] = A[i-1]+A[i-2];
 
    /* This is a way to initialize an array. */
    int *B[3] = { A, A+7, A+14 };
 
    /* We also could have done:
       int *B[3];
       B[0] = A;
       B[1] = A+7;
       B[2] = A+14;
     */
 
    printf("*A = %p\n", (A+6) );
 
    /* Note: I knew that B[1][2] is an integer.  But I also could
       have thought it was a pointer.  If so, I would have tried this:
 
    printf("B[1][2] = %p\n", B[1][2]);
  
       if I had done this, then the compiler would have issued a warning, such 
       as:
 
jd.c:14:30: warning: format specifies type 'void *' but the argument has type
      'int' [-Wformat]
    printf("B[1][2] = %p\n", B[1][2]);
                      ~~     ^~~~~~~
                      %d
1 warning generated.
     */
}