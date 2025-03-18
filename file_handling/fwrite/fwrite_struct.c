#include<stdio.h>
#include<stdlib.h>

typedef struct
{
	int id;
	char fname[15];
	char lname[15];
} employee;

int main()
{
	employee aInfo = {131, "Jessica", "Lillian"};
	FILE *fp = NULL;

	fp = fopen("Frank.dat", "wb");
	if(fp == NULL)
	{
		printf("Error!\n");
		exit(1);
	}

	fwrite(&aInfo, sizeof(aInfo), 1, fp);

	fclose(fp);

	return 0;
}
