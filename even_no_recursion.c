#include<stdio.h>

void even_num(int n)
{
	if(n == 0)
	{
		return;
	}

	even_num(n-1);

	if(n % 2 == 0)
	{
		printf("%d ", n);
	}
}

int main()
{
	int n;
	printf("Enter value of n = ");
	scanf("%d", &n);

	printf("Even numbers = ");
	even_num(n);
	printf("\n");

	return 0;
}
