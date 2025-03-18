#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 32

int main()
{
	FILE *fp = NULL;
	char name[MAX_SIZE] = {0};

	printf("Enter name: ");
	fgets(name, MAX_SIZE, stdin);

	fp = fopen("Jessica.txt", "w");
	if(fp == NULL)
	{
		printf("File not created!\n");
		exit(1);
	}

	fwrite(name, sizeof(char), MAX_SIZE, fp);

	fclose(fp);

	printf("File created successfully!\n");

	return 0;
}

