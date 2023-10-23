#include<stdio.h>

void swp( int* x, int* y)
{
	int tmp;
	tmp =*x;
	x=y;
	*y = tmp;
}

int main()
{
	int x = 1;
	int y = 2;
	swp(&x,&y);
	printf("%d, %d\n",x,y);
	return 0;
}
