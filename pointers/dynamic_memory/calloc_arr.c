#include<stdio.h>
#include<stdlib.h>

int main()
{
	int *arr;
	int n;
	
	printf("Enter number of elements:\n");
	scanf("%d", &n);

	arr = (int*) calloc(n, sizeof(int));

        printf("Enter array elements:");
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

	free(arr);

	return 0;
}
