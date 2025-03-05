#include<stdio.h>

int main()
{
	void *a = NULL;
	int *b = NULL;
	char *c = NULL;
	float *d = NULL;

	printf("Size of void pointer = %lu\n", sizeof(a));
	printf("Size of integer pointer = %lu\n", sizeof(b));
	printf("Size of character pointer = %lu\n", sizeof(c));
	printf("Size of float pointer = %lu\n", sizeof(d));

	return 0;
}
