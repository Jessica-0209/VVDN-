#include <stdio.h>

typedef unsigned int uint;

int clear_bit(uint data, uint pos)
{
    return (data & (~(1 << pos)));
}

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
    uint cData = 0;
    uint pos = 0;
    const int num_bits = sizeof(int) * 8;

    printf("Initially cData: \n");
    scanf("%u", &cData);

    printf("Binary of %u: ", cData);
    printBinary(cData, num_bits);

    printf("\nEnter the position to be cleared: ");
    scanf("%u",&pos);
    
    cData = clear_bit(cData,pos);
    
    printf("\n%uth Bit cleared.\nNow cData will be:\n",pos);
    printBinary(cData, num_bits);

    printf("\nValue after clearning %uth bit: %u.\n ", pos, cData);

    return 0;
}
