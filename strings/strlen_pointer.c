#include<stdio.h>

int str_length(char *str) //we are using int here because we are declaring something inside the function, and we need to return it so that it can be used in any other function.
{
	int count = 0;
	while(*str != '\0')
	{
		count++;
		str++;
	}
	return count;
}

int main()
{
	char str[] = "HeyyJesssicaa!";

	int count = str_length(str);
	printf("Length of string = %d\n", count);

	return 0;
}
