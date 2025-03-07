#include<stdio.h>
#include<stdlib.h>

int main()
{
	int *arr;

	arr = (int*) calloc(3, sizeof(int));

	arr[0] = 12;
	arr[1] = 13;
	arr[2] = 14;

	printf("Array elements before reallocation:\n");
	printf("%d %d %d", arr[0], arr[1], arr[2]);

	arr = (int*) realloc(arr, 4 * sizeof(int));

	arr[3] = 11;

	printf("\nArray elements after reallocation:\n");
	for(int i = 0; i < 4; i++)
	{
		printf("%d", arr[i]);
		printf(" ");
	}
	printf("\n");

	free(arr);

	return 0;
}
