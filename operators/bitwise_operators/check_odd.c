#include<stdio.h>

void print_binary(const int n, const int num_bits)
{
	for( int i = num_bits - 1; i >= 0; i--)
	{
		printf("%d", (n >> i) & 1);
		if (i % 4 == 0)
		{
			printf(" ");
		}
	}
}

int main()
{
	int n = 0;
	const int num_bits = sizeof(int) * 8;

	printf("Enter number:\n");
	scanf("%d", &n);

	printf("Binary representation of %d:\n", n);
	print_binary(n, num_bits);
	printf("\n");
	
	if(n & 1)
	{
		printf("Odd number!!\n");
	}
	else
	{
		printf("Even number!!\n");
	}

	return 0;
}
