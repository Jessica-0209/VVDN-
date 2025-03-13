#include<stdio.h>

union Test
{
	int x;
	char c[4];
};

int main()
{
	union Test t1 = {4};
	printf("%d\n", t1.x);

	union Test t2 = { .c = {"Aml"} };
	printf("%s\n", t2.c);
	
	return 0;
}
