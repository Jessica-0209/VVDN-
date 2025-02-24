#include<stdio.h>
int check_opposite(const int a, const int b)
{
    const int opp = ((a * b) < 0);
    return opp;
}
int main()
{
    int a = 0;
    int b = 0;

    printf("Enter the Value of a and b:\n ");
    scanf("%d%d", &a, &b);
    
    const int is_opposite = check_opposite(a, b);
    if (is_opposite)
    {
        printf ("Integers have the opposite sign\n");
    }
    else
    {
        printf ("Integer have the same sign\n");
    }

    return 0;
}
