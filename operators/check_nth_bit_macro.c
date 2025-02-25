#include <stdio.h>

#define IS_BIT_SET(value, pos) (value & (1U<< pos))

typedef unsigned int uint;

void print_binary(uint n, const int num_bits)
{
	for (int i = num_bits - 1; i >= 0; i--)
	{
		printf("%d", (n >> i) & 1);
		if ( i % 4 == 0)
		{
			printf(" ");
		}
	}
}

int main()
{
    uint cData = 0;
    uint pos = 0;
    const int num_bits = sizeof(int) * 8;

    printf("Initially cData: ");
    scanf("%u", &cData);

    printf("Binary of %u: \n", cData);
    print_binary(cData, num_bits);
    
    printf("\n\nEnter the position to be checked: ");
    scanf("%u",&pos);
    
    if( pos > num_bits - 1)
    {
	    printf("\nInvalid position!\nEnter between 0 and %d.\n", num_bits - 1);
	    return 1;
    }

    if(IS_BIT_SET(cData,pos))
    {
        printf("\nBit is One.\n");
    }
    else
    {
        printf("\nBit is zero.\n");
    }

    return 0;
}
