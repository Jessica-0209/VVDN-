#include<stdio.h>
#include<stdlib.h>

int main()
{
	int *arr;
	int n = 5;

	int *ptr;

	printf("Calloc for array elements:\n");
	arr = (int*) calloc(n, sizeof(int));

	printf("Enter array elements:\t");
	for(int i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}

	printf("Array elements: \n");
	for(int i = 0; i < n; i++)
	{
		printf("%d", arr[i]);
		printf(" ");
	}
	printf("\n");

	printf("\nCalloc for single integer:\n");
	ptr = (int*) calloc(1, sizeof(int));

	printf("Value of ptr before assigning: %d\n", *ptr);

	*ptr = 34;

	printf("Value of ptr after assigning: %d\n", *ptr);
	
	
	free(arr);
	free(ptr);

	return 0;
}
