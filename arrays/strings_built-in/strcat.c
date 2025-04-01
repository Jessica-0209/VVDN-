#include<stdio.h>
#include<string.h>

int main()
{
	char str1[] = "Heyyy";
	char str2[] = " Jessica!!";

	strcat(str1, str2);  //syntax: strcat(destination, source)
	printf("Concatenated string: %s\n", str1);

	return 0;
}
