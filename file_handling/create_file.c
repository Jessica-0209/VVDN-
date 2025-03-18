#include<stdio.h>
#include<stdlib.h>

int main()
{
	FILE *fp = NULL;

	fp = fopen("jessica.txt", "w");
	if(fp == NULL)
	{
		printf("File no created!\n");
		return -1;
	}
	else
	{
		printf("File is created!\n");
	}

	fclose(fp);
	
	return 0;
}
