#include<stdio.h>

typedef unsigned int uint;

const int num_bits = sizeof(int) * 8;

void print_binary(uint n)
{
	for(int i = num_bits - 1; i >= 0; i--)
	{
		printf("%d", (n >> i) & 1);
		if(i % 4 == 0)
		{
			printf(" ");
		}
	}
}

uint reverse_bits(uint num)
{
    uint reversed = 0;
    
    for (int i = 0; i < num_bits; i++)
    {
        reversed <<= 1;        
        reversed |= (num & 1); 
     	num >>= 1;             
    }

    return reversed;
}

int main()
{
    uint data = 0;
    uint rev = 0;
    
    printf("Enter the number: ");
    scanf("%u",&data);
    
    printf("\n\nEntered Data is:\n " );
    print_binary(data);
    
    
    rev = reverse_bits(data);
   
    printf("\n\nReverse Data is:\n ");
    print_binary(rev);

    printf("\n");
    
return 0;
}
