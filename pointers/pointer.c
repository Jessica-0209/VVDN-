#include<stdio.h>

int main(void)
{
	int data = 20;
	int *ptr = NULL;
	ptr = &data;

	printf("Address of data: %p\n", &data);

	printf("Address stored in ptr: %p\n", ptr);

	printf("Value of *ptr: %d\n", *ptr);

	*ptr = 6;

	printf("New value of *ptr = %d\n", *ptr);

	printf("data = %d\n", data);

	return 0;
}
