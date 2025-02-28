#include<stdio.h>

void swap(int x, int y)
{
	int temp;

	temp = x;
	x = y;
	y = temp;

	printf("Value inside the swap function.\n");
	printf("x = %d, y = %d\n", x, y);
}

int main()
{
	int x = 0;
	int y = 0;

	printf("Enter values for x and y: \n");
	scanf("%d%d", &x, &y);

	printf("x and y before swapping.\n");
	printf("x = %d, y = %d\n", x, y);

	swap(x, y);

	printf("x and y after swapping.\n");
	printf("x = %d, y = %d\n", x, y);

	return 0;
}
