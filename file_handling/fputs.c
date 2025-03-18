#include<stdio.h>
#include<stdlib.h>

int main()
{
	FILE *fp = NULL;

	fp = fopen("JO.txt", "w+");
	if(fp == NULL)
	{
		printf("File not created!\n");
		exit(1);
	}

	fputs("Heyy JO! I am Jessica!\n", fp);

	fclose(fp);

	return 0;
}
