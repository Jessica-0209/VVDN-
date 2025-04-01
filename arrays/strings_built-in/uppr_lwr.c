#include<stdio.h>
#include<ctype.h>

void to_upper(char str[])
{
	for(int i = 0; str[i] != '\0'; i++)
	{
		str[i] = toupper(str[i]);
	}
}

void to_lower(char str[])
{
	for(int i = 0; str[i] != '\0'; i++)
	{
		str[i] = tolower(str[i]);
	}
}

int main()
{
	char str[] = "JeSsIcA";

	printf("Original string is %s\n", str);

	to_upper(str);
	printf("Uppercase string is %s\n", str);

	to_lower(str);
	printf("Lowercase string is %s\n", str);

	return 0;
}
