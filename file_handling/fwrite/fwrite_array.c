#include<stdio.h>
#include<stdlib.h>

int main()
{
	int data[] = {32, 43, 53, 132, 43, 23, 9};
	FILE *fp = NULL;

	fp = fopen("Jessica.dat", "wb");
	if(fp == NULL)
	{
		printf("Error!\n");
		exit(1);
	}

	fwrite(data, sizeof(data), 1, fp);

	fclose(fp);

	return 0;
}
