#include<stdio.h>

void print_num(int n)
{
	if(n == 0)
	{
		return;
	}

	print_num(n-1);
	printf("%d ", n);
}

int main()
{	
	int n;
	printf("Enter value of n = ");
	scanf("%d", &n);
	
	printf("Numbers = ");
	print_num(n);
	printf("\n");

	return 0;
}
