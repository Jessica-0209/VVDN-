#include<stdio.h>

#define set_bit(value, pos) (value | (1 << pos))

typedef unsigned int uint;

void printBinary(uint n, const int num_bits)
{
    for (int i = num_bits - 1; i >= 0; i--)
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
	uint value = 0;
	uint pos = 0;
	const int num_bits = sizeof(int) * 8;

	printf("Enter value: ");
	scanf("%u", &value);

	printf("\nBinary of %u: ", value);
	printBinary(value, num_bits);

	printf("\nEnter the position to be set: ");
	scanf("%u", &pos);

	if(pos > num_bits - 1)
	{
		printf("\nInvalid position!\nPlease enter between 0 and %d.\n", num_bits - 1);
        	return 1; 
    	}

	value = set_bit(value, pos);

	printf("\nBinary after setting bit: ");
        printBinary(value, num_bits);


	printf("\nAfter setting %uth bit, data will be: %u\n", pos, value);

	return 0;
}
