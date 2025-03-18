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
	employee emp[] = 
	{
		{1, "Jessica", "Joshy"},
		{2, "Franklin", "Mathew"},
		{3, "Jessica", "Lillian"},
		{4, "Franklin", "Joshy"},
	};
	FILE *fp = NULL;

	fp = fopen("Frank.dat", "wb");
	if(fp == NULL)
	{
		printf("Error!\n");
		exit(1);
	}

	fwrite(emp, sizeof(emp), 1, fp);

	fclose(fp);

	return 0;
}
