#include <stdio.h>

int divint( int a, int b )
{
	return a/b;
}

int main()
{
	int a = 10;
	int b = 10;
	int c = divint(a, b);
	printf("a / b = %d\n", c );

	c = divint(a, b);
	printf("a / b = %d\n", c );
}
