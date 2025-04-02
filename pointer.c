#include<stdio.h>

int main()
{
	char *p;
	p = "Hello";
	printf("%c\n", *&*p);
	printf("test\n");
	printf("%c\n",*p);

	return 0;
}
