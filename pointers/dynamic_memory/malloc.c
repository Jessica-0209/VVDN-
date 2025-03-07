#include<stdio.h>
#include<stdlib.h>

int main()
{
	int *ptr;

	ptr = (int*) malloc(sizeof(int));

	*ptr = 45;

	printf("Value stored dynamically: %d\n", *ptr);
	
	free(ptr);

	return 0;
}
