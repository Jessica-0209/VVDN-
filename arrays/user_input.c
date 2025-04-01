#include<stdio.h>

int main()
{
	int arr[5];
	int i;

	printf("Enter elements: \n");
	for(i = 0; i < 5; i++)
	{
		scanf("%d", &arr[i]);
	}

	printf("Print array elements\n");
	for(i = 0; i < 5; i++)
	{
		printf("%d\t", arr[i]);
	}
	printf("\n");	
	return 0;
}
