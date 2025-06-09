#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TABLE_SIZE 50

typedef struct
{
	int usn;
	char name[20];
	char class[10];
	struct Student *next;
} Student;

Student *hash_table[TABLE_SIZE];

unsigned int hash(int usn)
{
	return usn % TABLE_SIZE;
}

void insert(int usn, const char *name, const char *class)
{
	unsigned int index = hash(usn);
	Student *current = hash_table[index];

	while(current)
	{
		if(current->usn == usn)
		{
			printf("Student with usn %d already exists.\n", usn);
			return;
		}
		current = current->next;
	}


