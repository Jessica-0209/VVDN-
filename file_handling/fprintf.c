#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	FILE *fp = NULL;

	char *message = "Jessica! HI!";
	int length = 0;

	fp = fopen("Jessica.txt", "w");
	if(fp == NULL)
	{
		printf("Error in creating file!");
		exit(1);
	}

	length = strlen(message);

	fprintf(fp, "%d", length);
	fprintf(fp, "%s", message);

	fclose(fp);

	return 0;
}
