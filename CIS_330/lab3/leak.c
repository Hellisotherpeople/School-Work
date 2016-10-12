#include <stdio.h>
#include <stdlib.h>

int main()
{
	int num = 1000;
	double* p = (double*) malloc( num * sizeof(double) );
	free(p); 
	printf("I remembered to clean up my trace \n" );
}
