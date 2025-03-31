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

void str_reverse(char str[])
{
	int len = str_length(str);
	for(int i = 0; i < len/2; i++)
	{
		char temp = str[i];
		str[i] = str[len-i-1];
		str[len-i-1] = temp;
	}
}

int main()
{
	char str[] = "Notepad";
	printf("Original string = %s\n", str);

	str_reverse(str);
	printf("Reversed string = %s\n", str);

	return 0;
}
