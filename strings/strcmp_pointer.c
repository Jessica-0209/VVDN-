#include<stdio.h>

int str_compare(const char *str1, const char *str2)
{
	while(*str1 != '\0' && *str2 != '\0')
	{
		if(*str1 != *str2)
		{
			return *str1 - *str2;
		}
		str1++;
		str2++;
	}
	return *str1 - *str2;
}

int main()
{
	char str1[] = "Jessicaaaa";
	char str2[] = "Joanne";

	int result = str_compare(str1, str2);
	printf("Compare 2 strings: %d\n", result);

	if(result == 0)
	{
		printf("Strings are equal!\n");
	}
	else if(result < 0)
	{
		printf("String 1 is smaller than string 2!\n");
	}
	else
	{
		printf("String 1 is bigger than string 2!\n");
	}

	return 0;
}
