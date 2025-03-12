#include<stdio.h>
#include<string.h>

union Data
{
	int i;
	float f;
	char str[20];
} data;

int main()
{
	data.i = 10;
	printf("data.i = %d\n", data.i);

	data.f = 120.24;
	printf("data.f = %.2f\n", data.f);

	strcpy(data.str, "Heyy");
	printf("data.str = %s\n", data.str);

	printf("After writing string, data.i = %d\n", data.i);
	
	return 0;
}

