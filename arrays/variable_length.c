#include<stdio.h>

void display(int n)
{
	int arr[n];
	int i = 0;

	printf("Elements of array are: \n");
	for(i = 0; i < n; i++)
	{
		arr[i] = i;
		printf("%d\t", arr[i]);
	}
	printf("\n");
}

int main()
{
	int n;

	printf("Enter size of array:\n");
	scanf("%d", &n);

	display(n);

	return 0;
}
