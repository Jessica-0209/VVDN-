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
	
	employee aInfo = {0};
	FILE *fp = NULL;

	fp = fopen("Frank.dat", "rb");
	if(fp == NULL)
	{
		printf("Error!\n");
		exit(1);
	}

	fread(&aInfo, sizeof(aInfo), 1, fp);
	
	printf("Employee details:\n");
	printf("ID: %d\n", aInfo.id);
	printf("First Name: %s\n", aInfo.fname);
	printf("Last Name: %s\n", aInfo.lname);

	fclose(fp);

	return 0;
}
