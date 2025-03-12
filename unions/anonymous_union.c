#include<stdio.h>

struct color_code
{
	union
	{
		char m;
		unsigned int n;
	};
} ascii, ch;

int main()
{
	ascii.n = 65;
	ch.m = 'A';

	printf("ch.m = %c\n", ch.m);
	printf("ascii.n = %d\n", ascii.n);
	
	return 0;
}
