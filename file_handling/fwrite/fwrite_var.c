#include<stdio.h>
#include<stdlib.h>

int main()
{
	int data = 34;
	FILE *fp = NULL;

	fp = fopen("Jessica.dat", "wb");
	if(fp == NULL)
	{
		printf("Error in creating file!\n");
		exit(1);
	}

	fwrite(&data, sizeof(data), 1, fp);

	fclose(fp);

	return 0;
}
