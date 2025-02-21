#include<stdio.h>


int main()
{
    int result = 0;
    float div = 0.0;
    int a;
    int b;

    printf("Enter values for a and b: ");
    scanf("%d%d", &a, &b);

    result = a + b;
    printf("Addition result = %d\n", result);

    result = a - b;
    printf("Subtraction result = %d\n", result);

    result = a * b;
    printf("Multiplication result = %d\n", result);

    div = a / b;
    printf("Division result = %.1f\n", div); 

    result = a % b;
    printf("Modulo result = %d\n", result);


}
