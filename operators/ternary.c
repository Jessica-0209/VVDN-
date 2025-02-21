#include<stdio.h>

int main()
{
	int a;
	int b;

	printf("Enter values of a and b:\n");
	scanf("%d%d", &a, &b);

        int max = (a > b) ? a : b;

	printf("Maximum of %d and %d is %d\n", a, b, max);

	return 0;
}
