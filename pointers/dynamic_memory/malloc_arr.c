#include<stdio.h>
#include<stdlib.h>

int main()
{
	int *arr;
	int n;

	printf("Enter number of elements:\n");
	scanf("%d", &n);

	arr = (int*) malloc(sizeof(int));

	for(int i = 0; i < n; i++)
	{
		arr[i] = i * 5;
	}

	printf("Array elements:\n");
	for(int i = 0; i < n; i++ )
	{
		printf("%d", arr[i]);
		printf(" ");
	}
	printf("\n");

	free(arr);
	
	return 0;
}
