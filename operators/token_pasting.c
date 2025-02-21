#include<stdio.h>

#define TEST1(token1, token2) token1##token2
#define TEST2(token) var##token
#define TEST3(token) token##var
#define TEST4 var##4
#define CREATE_3_VAR(name) name##6, name##7, name##8

int main()
{
	int var1 = 10;
	int var2 = 20;
	int _var = 30;
	int var4 = 40;
	int CREATE_3_VAR(var);

	var6 = 50;
	var7 = 60;
	var8 = 70;

	printf("%d\n", TEST1(var, 1));
	printf("%d\n", TEST2(2));
	printf("%d\n", TEST3(_));
	printf("%d\n", TEST4);
	//printf("%d\n", TEST1(var, +));  invalid
	//printf("%d\n", TEST1(var, 5));  invalid
	printf("%d\n", var6);
	printf("%d\n", var7);
	printf("%d\n", var8);

	return 0;
}

