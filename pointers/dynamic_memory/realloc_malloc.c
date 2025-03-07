#include<stdio.h>
#include<stdlib.h>

int main()
{
	int *arr;

	arr = (int*) malloc(2 * sizeof(int));

	arr[0] = 12;
	arr[1] = 23;

	printf("Array elements before reallocation:\n");
	printf("%d %d", arr[0], arr[1]);


	arr = (int*) realloc(arr, 4 * sizeof(int));

	arr[2] = 44;
	arr[3] = 13;

	printf("\nArray elements after reallocation of memory:\n");
	for(int i = 0; i < 4; i++)
	{
		printf("%d", arr[i]);
		printf(" ");
	}
	printf("\n");

	free(arr);

	return 0;
}
