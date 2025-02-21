#include<stdio.h>


int main()
{
	int a = 100;
	int b = 200;
	int c;
	int d;


	c = ++a; //value of a is incremented and then c is updated.
	d = b--; //d gets old value of b, and then b is decremented.


	printf("A = %d\n", a);
	printf("B = %d\n", b);
        printf("C = %d\n", c);
        printf("D = %d\n", d);


	return 0;
}
