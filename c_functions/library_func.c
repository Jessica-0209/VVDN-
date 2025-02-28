#include<stdio.h>
#include<string.h>

int main()
{
        char name[30] = {0};
	char surname[30] = {0};
	char fullname[100] = {0};
        int length;

        strcpy(name, "Jessica"); 
	printf("Name = %s\n", name);

        length = strlen(name);
        printf("Length = %d\n", length);
	
	strcpy(surname, "Lillian");

	strcpy(fullname, name);
	strcat(fullname, " ");
	strcat(fullname, surname);
	printf("Fullname = %s\n", fullname);

        return 0;
}

