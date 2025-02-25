#include<stdio.h>

#define clear_bit(value, pos) (value & ~(1 << pos))

typedef unsigned int uint;

void printBinary(uint n, const int num_bits)
{
	for(int i = num_bits - 1; i >= 0; i--)
	{
		printf("%d", (n >> i) & 1);
		if( i % 4 == 0)
		{
			printf(" ");
		}
	}
}

int main()
{
	uint value = 0;
	uint pos = 0;
	const int num_bits = sizeof(int) * 8;

	printf("Enter value: ");
	scanf("%u", &value);

	printf("Binary of %u: \n", value);
	printBinary(value, num_bits);

	printf("\n\nEnter position to be cleared: ");
	scanf("%u", &pos);

	if (pos > num_bits - 1)
	{
		printf("Invalid position!\nPlease enter between 0 and %d.\n", num_bits - 1);
		return 1;
	}

	value = clear_bit(value, pos);

	printf("Binary after clearing bit: \n");
	printBinary(value, num_bits);

	printf("\n\nValue after clearing bit: %u\n", value);

	return 0;
}

