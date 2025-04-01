#include<stdio.h>
#include<string.h>

int main()
{
	char str1[] = "Jessica";
	char str2[] = "Joanne";

	int result = strcmp(str1, str2);
	printf("%d\n", result);

	if(result == 0)
	{
		printf("Strings are equal!\n");
	}
	else if(result < 0)
	{
		printf("str1 is smaller than str2!\n");
	}
	else
	{
		printf("str1 is greater than str2!\n");
	}

	return 0;
}
