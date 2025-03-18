#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 32

int main()
{
	FILE *fp = NULL;
	char file_data[MAX_SIZE] = {0}; 

	fp = fopen("JO.txt", "r");
	if(fp == NULL)
	{
		printf("File not created!\n");
		exit(1);
	}

	fread(file_data, sizeof(char), 10, fp);

	puts(file_data);

	fclose(fp);

	printf("File read successfully!\n");

	return 0;
}
