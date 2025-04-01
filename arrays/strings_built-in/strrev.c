#include<stdio.h>
#include<string.h>

void strrev(char str[])
{
	int len = strlen(str);
	for(int i = 0; i < len/2; i++)
	{
		char temp = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = temp;
		
		printf("Step %d: %s\n", i + 1, str);
	}
}

int main()
{
	char str[] = "Jessica";
	printf("String is %s\n\n", str);
	strrev(str);
	printf("\nReverse is %s\n", str);

	return 0;
}
