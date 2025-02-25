#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;

void print_binary(uint n, const int num_bits)
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
    int pos = 0;
    const int num_bits = sizeof(int) * 8;
    
    //system("COLOR F");  line changes bg color on windows, however, it is ignored on linux.

    printf("Initially cData: ");
    scanf("%u", &cData);

    printf("\nBinary of %u: ", cData);
    print_binary(cData, num_bits);
    
    printf("\nEnter the position to be toggled: ");
    scanf("%u",&pos);

    if (pos > num_bits - 1)
    {
	    printf("\nInvalid position!\nEnter between 0 and %d,\n", num_bits - 1);
	    return 1;
    }
    
    cData ^= 1 << pos;

    printf("\nBinary after toggling bit: \n");
    print_binary(cData, num_bits);
    
    printf("\n\n%uth Bit toggled.\nNow cData will be: %u\n ",pos, cData);
    return 0;

}
