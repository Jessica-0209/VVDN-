#include<stdio.h>

void str_concat(char *dest, char *src)
{
	while(*dest != '\0')
	{
		*dest++;
	}

	while(*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';	
}

int main()
{
	char str1[] = "Hiii, ";
	char str2[] = "Jessica here!";
	printf("Original strings are: %s and %s\n", str1, str2);

	str_concat(str1, str2);

	printf("Appended string: %s\n", str1);

	return 0;
}
