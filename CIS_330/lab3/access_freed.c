#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("hint: do all the writes and reads of p valid?\n\n");

	int num = 5;
	double* p = (double*)malloc( num * sizeof(double) );
	int i;
	double t;
	for( i = 0; i < num; i++ )
	{
		t = i * 3.14 * -1;
		p[i] = t;
	}

	
	printf(" 1st element in p is: %f\n", p[0] );

	p[2] = 200;
	printf(" 3rd element is assigned: %f\n", p[2] );
	free(p);
}
