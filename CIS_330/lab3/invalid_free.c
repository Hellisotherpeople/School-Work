#include <stdio.h>
#include <stdlib.h>

int main()
{
	int num = 10;
	double* p = (double*)malloc( num * sizeof(double) );
	double* p2 = p;
	int i;
	double t;
	for( i = 0; i < num; i++ )
	{
		t = i * 3.14 * -1;
		p[i] = t;
	}

	free( p );
	printf(" 1st element in p is: %f\n", p[0] );

	free( p2 );
}
