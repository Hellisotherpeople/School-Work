#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	printf(" arr is filled with negative numbers. does the print statement agree?\n");
			

	int* arr = (int*) malloc( 5 * sizeof(int) );
	int i, t;
	srand(time(NULL));
	for( i = 0; i < 5; i++ )
	{
		t = rand();
		if( t > 0 )
			t = t * -1;
		arr[i] = t; 
	}

	int first = arr[1];
	int last = arr[5];

	printf("first element = %d\n", first );
	printf("last element = %d\n", last );

	free (arr);
}
