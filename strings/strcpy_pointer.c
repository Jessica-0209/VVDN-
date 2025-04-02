#include<stdio.h>

void str_copy(char *dest, const char * src)
{
	while(*src != '\0')
	{
		*dest = *src;
		*src++;  //try to understand this again after you're done with all
		*dest++;
	}
	*dest = '\0';
}

int main()
{
	char src[] = "Jessica";
	char dest[20];

	str_copy(dest, src);
	printf("Copied string is %s\n", dest);

	return 0;
}
