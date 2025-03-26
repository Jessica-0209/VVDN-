#include<stdio.h>

void multiple_3(int n)
{
/*	if(n == 0)
	{
		return;
	}
*/
	multiple_3(n-1);
	if(n % 3 == 0)
	{
		printf("%d ", n);
	}
}

int main()
{
	int n;
	printf("Enter n = ");
	scanf("%d", &n);

	printf("Multiples of 3 = ");
	multiple_3(n);
	printf("\n");

	return 0;
}
