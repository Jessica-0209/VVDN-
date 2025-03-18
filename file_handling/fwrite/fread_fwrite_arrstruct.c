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
        employee emp[10] = {0};
        FILE *fp = NULL;

        fp = fopen("Frank.dat", "rb");
        if(fp == NULL)
        {
                printf("Error!\n");
                exit(1);
        }

        fread(emp, sizeof(employee), 4, fp);

        fclose(fp);

	printf("Employee details:\n");
	for(int i = 0; i < 4; i++)
	{
		printf("ID = %d\n", emp[i].id);
		printf("First Name = %s\n", emp[i].fname);
		printf("Last Name = %s\n", emp[i].lname);
		printf("\n");
	}

        return 0;
}

