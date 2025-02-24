#include<stdio.h>

typedef unsigned int uint;

void printBinary(unsigned int num)
{
    for (int i = 31; i >= 0; i--)
    {
        printf("%d", (num >> i) & 1);
        if (i % 4 == 0)
        {
            printf(" ");
	}
    }
}

int set_bit(uint data, uint pos)
{
	return (data | (1 << pos));
}

int main()
{
	uint cData = 0;
	uint pos;
	const int num_bits = sizeof(int) * 8;

	printf("cData: ");
	printBinary(cData);
	printf("\n");

	printf("Enter the position to be set: ");
	scanf("%u", &pos);

	if(pos > num_bits - 1)
	{
		printf("Invalid position!\nPlease choose a position between 0 and %d.\n", num_bits - 1);
		return 1;
	}
	cData = set_bit(cData, pos);

	printf("%dth bit set.\nNow cData will be: ", pos);
	printBinary(cData);
	printf("\n");

	return 0;
}
