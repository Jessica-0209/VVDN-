#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main()
{
	FILE *fp = NULL;

	char *message = "Hey Jessica!";
	int length = 0;

	fp = fopen("Jessica.dat", "wb");
	if(fp == NULL)
	{
		printf("Error in creating file!\n");
		exit(1);
	}

	length = strlen(message);

	fwrite(&length, sizeof(int), 1, fp);

	fwrite(message, sizeof(char), length, fp);

	fclose(fp);

	return 0;
}
