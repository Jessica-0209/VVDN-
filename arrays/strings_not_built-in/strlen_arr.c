#include<stdio.h>

int str_length(char str[])
{
	int count = 0;
	for(int i = 0; str[i] != '\0'; i++)
	{
		count++;
	}
	return count;
}

int main()
{
	char str[] = "Jessica!";
	printf("String = %s\n", str);

	int count = str_length(str);
	printf("String length = %d\n", count);

	return 0;
}
