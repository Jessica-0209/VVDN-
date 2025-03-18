#include<stdio.h>
#include<stdlib.h>

int main()
{
	FILE *fp = NULL;
	int length = 0;
	char *message = NULL;

	fp = fopen("Jessica.dat", "rb");
	if(fp == NULL)
	{
		printf("Error in creating file\n");
		exit(1);
	}

	fread(&length, sizeof(int), 1, fp);
	printf("Message length: %d\n", length);

	message = (char*)malloc(length + 1);
	if(message == NULL)
	{
		printf("Memory allocation failed!\n");
		exit(1);
	}
	
	fread(message, sizeof(char), length, fp);

	message[length] = '\0';

	printf("Message from file: %s\n", message);

	free(message);
	free(fp);

	return 0;
}
