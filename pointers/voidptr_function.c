#include<stdio.h>

void print_value(void *ptr, char type)
{
	if (type == 'i')
	{
		printf("Integer: %d\n", *(int*)ptr);
	}
	else if (type == 'f')
	{
		printf("Float: %.2f\n", *(float*)ptr);
	}
	else if (type == 'c')
	{
		printf("Character: %c\n", *(char*)ptr);
	}
}

int main()
{
	int num = 200;
	float pi = 3.14;
	char ch = 'J';

	print_value(&num, 'i');
	print_value(&pi, 'f');
	print_value(&ch, 'c');

	return 0;
}
