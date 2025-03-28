#include<stdio.h>

void rev_num(int n)
{
	if(n == 0)
	{
		return;
	}

	printf("%d ", n);
	rev_num(n-1);
}

int main()
{
	int n;
	printf("Enter n = ");
	scanf("%d",&n);

	printf("Reverse numbers = ");
	rev_num(n);
	printf("\n");

	return 0;
}
