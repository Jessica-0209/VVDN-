#include<stdio.h>
#include<string.h>

int main()
{
	char name[30] = {0};
	int length;

	strcpy(name, "Jessica");

	length = strlen(name);
	printf("Length = %d\n", length);

	printf("Name = %s\n", name);

	return 0;
}

