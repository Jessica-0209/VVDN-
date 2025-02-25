#include <stdio.h>
#define SET     1
#define NOT_SET 0

typedef unsigned int uint;

void printBinary(uint n, const int num_bits)
{
	for(int i = num_bits - 1; i >= 0; i--)
	{
		printf("%d", (n >> i) & 1);
		if (i % 4 == 0)
		{
			printf(" ");
		}
	}
}

int is_nth_bit_set(uint data, uint pos)
{
    return ((data & (1 << pos))? SET : NOT_SET);
}

int main()
{
    uint cData = 0;
    uint pos = 0;
    uint is_bit_set = 0;
    const int num_bits = sizeof(int) * 8;
    
    printf("Initially cData:");
    scanf("%u", &cData);

    printf("Binary of %u: \n", cData);
    printBinary(cData, num_bits);

    printf("\n\nEnter the position to be checked: ");
    scanf("%u",&pos);
    
    if (pos > num_bits - 1)
    {
	    printf("\nInvalid position!.\nEnter between 0 and %d.\n", num_bits - 1);
	    return 1;
    }

    is_bit_set  = is_nth_bit_set(cData, pos);
    
    if(is_bit_set)
    {
        printf("\nBit is One\n");
    }
    else
    {
        printf("\nBit is zero\n");
    }
    return 0;

}
