#include<stdio.h>

int check_opp_sign(const int a, const int b)
{
	const int opp = ((a ^ b) < 0);
	return opp;
}

int main()
{
	int a = 0;
	int b = 0;

	printf("Enter value of a and b: \n");
	scanf("%d%d", &a, &b);

	const int is_opposite = check_opp_sign(a, b);
	if (is_opposite)
	{
		printf("Integers have opposite sign\n");
	}
	else
	{
		printf("Integers have the same sign\n");
	}
	
	return 0;
}
