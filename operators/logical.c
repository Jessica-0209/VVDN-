#include<stdio.h>

int main()
{
    int a = 0;
    int b = 0;

    printf("Enter values of a and b:\n");
    scanf("%d%d", &a, &b);

    if ((a < 10 && b > 20 ) || (a >= 30))
    {
        printf("Hi!\n");
    }
    if (!(a == b))
    {
	    printf("Nothing!\n");
    }
    else
    {
        printf("Bye!\n");
    }

    return 0;
}
