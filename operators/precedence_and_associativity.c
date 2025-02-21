#include<stdio.h>

int main()
{
	float a = 5;
	float b = 10;
	float c;
	float d;
	float e;

	c = a * 2 + b;
	d = a * 3 + b / 2;
	e = ((a + 3) / (b * 2));

	printf("C = %.1f\n", c);
	printf("D = %.1f\n", d);
	printf("E = %.1f\n", e);

	return 0;
}

