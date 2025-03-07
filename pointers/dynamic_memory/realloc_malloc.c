#include<stdio.h>
#include<stdlib.h>

int void_fun(void *var, char type)
{
	switch (type) 
	{
		case 'i': 
            		printf("Print values: %d \n", *(int*)var);
            		break;
        	case 'f': 
            		printf("Print values: %.2f \n", *(float*)var);
            		break;
        	case 'c': 
            		printf("Print values: %c \n", *(char*)var);
            		break;
        	default:
            		printf("Unknown type\n");
	}
}


int main()
{
	int *arr;
	int m;

	printf("Enter number of elements:\n");
	scanf("%d", &m);

	arr = malloc(sizeof(int));

	printf("Array elements before reallocation:\n");
	for(int i = 0; i < m; i++)
	{
		arr[i] = i * 2;
		printf("%d", arr[i]);
		printf(" ");
	}
	printf("\n");


	arr = (int*) realloc(arr,7 * sizeof(int));

	arr[5] = 44;
	arr[6] = 13;

	printf("\nArray elements after reallocation of memory:\n");
	for(int i = 0; i < 7; i++)
	{
		printf("%d", arr[i]);
		printf(" ");
	}
	printf("\n");

	free(arr);

	int c = 6;
	float a = 2.7;
	char b = 'V';

	void_fun(&c, 'i');
	void_fun(&a, 'f');
	void_fun(&b, 'c');


	return 0;
}
