#include<stdio.h>

int main()
{
    int a = 0;

    printf("Enter value:\n");
    scanf("%d", &a);

    if (a <= 100)
    {
        printf("Hi!\n");
    }
    else
    {
        printf("Bye!\n");
    }

    return 0;
}
