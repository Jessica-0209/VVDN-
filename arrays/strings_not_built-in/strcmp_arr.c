#include<stdio.h>

int str_compare(const char str1[], const char str2[])
{
	int i = 0;

	while(str1[i] != '\0' && str2[i] != '\0')
	{
		if(str1[i] != str2[i])
		{
			return str1[i] - str2[i];
		}
		i++;
	}
	return str1[i] - str2[i];
}

int main()
{
	char str1[] = "Hey";
	char str2[] = "There";

	int result = str_compare(str1, str2);
	printf("Compare 2 strings: %d\n", result);
	if(result == 0)
	{
		printf("Strings are equal!\n");
	}
	else if(result < 0)
	{
		printf("String1 is smaller than string2!\n");
	}
	else
	{
		printf("String1 is bigger than string2!\n");
	}

	return 0;
}

