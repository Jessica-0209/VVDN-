#include <stdio.h>

int binary[64] = {0}; 

void count_bits(const int num_bits)
{
    int count_0 = 0;
    int count_1 = 0;
    int i = 0;

    for (i = 0; i < num_bits; i++)
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

void decimal_to_binary(int n, const int num_bits)
{
    int i = 0;
    int j = 0;

    for (i = 0; i < num_bits; i++)
    {
        binary[i] = 0;
    }

    for (i = num_bits - 1; n > 0; i--)
    {
        binary[i] = n % 2;
        n = n / 2;
    }

    printf("Binary: ");
    for (j = 0; j < num_bits; j++)
    {
        printf("%d", binary[j]);
    }
    printf("\n");

    count_bits(num_bits);
}

int main()
{
    int num;
    int num_bits = sizeof(int) * 8;

    printf("Enter decimal value: ");
    scanf("%d", &num);

    if (num == 0)
    {
        printf("Binary: 0");
        printf("Number of 0s: 0\n");
        printf("Number of 1s: 0\n");
    }
    else
    {
        decimal_to_binary(num, num_bits);
    }

    return 0;
}

