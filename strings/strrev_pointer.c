#include<stdio.h>

void str_reverse(char *str)
{
	char *start = str;
	char *end = str;

	while(*end != '\0')
	{
		end++;
	}
	end--;

	while(start < end)
	{
		char temp = *start;
		*start = *end;
		*end = temp;

		start++;
		end--;
	}
}

int main()
{
	char str[] = "Water";
	printf("Original string: %s\n", str);

	str_reverse(str);
	printf("Reversed string: %s\n", str);

	return 0;
}
