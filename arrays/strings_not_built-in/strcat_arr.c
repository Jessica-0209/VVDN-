#include<stdio.h>

void str_concatenate(char dest[], const char src[])
{
	int i = 0;
	int j = 0;

	while(dest[i] != '\0')   //move dest[] to its last character 
	{
		i++;
	}

	while(src[j] != '\0')   //and then copy the src[] to dest[]
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	dest[i] = '\0';
}

int main()
{
	char str1[] = "Jessica";
	char str2[50] = " Lillian";

	str_concatenate(str1, str2);
	printf("Concatenated string = %s\n", str1);

	return 0;
}
