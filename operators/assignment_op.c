#include<stdio.h>

int main()
{
	int x;
	int y;

	printf("Enter values of x and y:\n");
	scanf("%d%d", &x, &y);

	x += 10;
	y *= 5;

	printf("X = %d\n", x);
	printf("Y = %d\n", y);

	return 0;
}

