#include<stdio.h>
#include<stdlib.h>

int main()
{
	int *ptr;

	ptr = (int*) calloc(1, sizeof(int));

	printf("Value of ptr before assigning: %d\n", *ptr);

	*ptr = 34;

	printf("Value of ptr after assigning: %d\n", *ptr);
	
	free(ptr);

	return 0;
}
