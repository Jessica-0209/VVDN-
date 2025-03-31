#include<stdio.h>

extern char src[] = "jessica";
void str_copy(char dest[], const char src[])
{
	int i = 0;
	while(src[i] != '\0')
	{
		dest[i] = src[i];
		printf("%s", src);
		i++;
	}
	dest[i] = '\0';
}

int main()
{
	//char src[] = {'r','y'};//causes array overflow as there is no end, since it is not reaching null at all.
	//char src[] = "jessica";
	//char src[] = {'j', 'e', 's', 's', '\0'};
	char dest[20];

	str_copy(dest, src);

	printf("Copied string is %s\n", dest);

	return 0;
}
