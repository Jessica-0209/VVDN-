#include<stdio.h>

int binary[32] = {0};
void count_bits(int length)
{
	int count_0 = 0;
	int count_1 = 0;
	int i = 0;

	for(i = 0; i < length; i++)
	{
		if (binary[i] == 1)
		{
			count_1++;
		}
		else
		{
			count_0++;
		}
	}
	printf("Number of 0s: %d\n", count_0);
	printf("Number of 1s: %d\n", count_1);
}

void decimal_to_binary(int n)
{
	int i = 0;
	int j = 0;

	for(i = 0; n > 0; i++)
	{
		binary[i] = n % 2;
		n = n / 2;
	}

	printf("Binary: ");
	for( j = i - 1; j >= 0; j--)
	{
		printf("%d", binary[j]);
	}
	printf("\n");
	count_bits(i);
}

int main()
{
	int num;
	
	printf("Enter decimal value: ");
	scanf("%d", &num);

	if(num == 0)
	{
		printf("Binary: 0\n");
		printf("Number of 0s: 0\n");
		printf("Number of 1s: 0\n");
	}
	else
	{
		decimal_to_binary(num);
	}

	return 0;
}
