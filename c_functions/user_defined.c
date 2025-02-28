#include<stdio.h>

int add_num(const int a, const int b); //function declaration

int main()
{
	int num1, num2, sum;

	printf("Enter 2 numbers: \n");
	scanf("%d%d", &num1, &num2);

	sum = add_num(num1, num2); //function call

	printf("Sum: %d\n", sum);

	return 0;
}

int add_num(const int a, const int b) //function definition
{
	int result = a + b;
	return result;
}
