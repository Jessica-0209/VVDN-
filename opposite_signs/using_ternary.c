#include<stdio.h>
int main()
{
    int a = 0;
    int b = 0;
   
    printf("Enter the Value of a and b:\n");
    scanf("%d%d", &a, &b);
 
    const int is_opposite = (a < 0)? (b >= 0): (b < 0);
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
