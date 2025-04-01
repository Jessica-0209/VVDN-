#include<stdio.h>

int main()
{
	int arr[20] = {1, 2, 3, [15] = 40, [13] = 80};
	int i = 0;
	
	printf("Elements stored in the array\n");
	for(i = 0; i < 20; i++)
	{
		printf("arr[%d] = %d\n", i, arr[i]);
	}
	return 0;
}
