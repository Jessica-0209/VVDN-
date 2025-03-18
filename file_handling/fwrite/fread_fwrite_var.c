#include<stdio.h>
#include<stdlib.h>

int main()
{
	int data = 0;
	FILE *fp = NULL;

	fp = fopen("Jessica.dat", "rb");
	if(fp == NULL)
	{
		printf("Error in creating file!\n");
		exit(1);
	}

	fread(&data, sizeof(int), 1, fp);
	printf("Data = %d\n", data);

	fclose(fp);

	return 0;
}
