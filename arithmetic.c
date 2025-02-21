#include<stdio.h>

int main()
{
	int a;
	int b;
	int result = 0;

	printf("Enter values for a and b: \n");
	scanf("%d%d", &a, &b);

	result = a + b;
	printf("Addition result = %d\n", result);

	return 0;

}

