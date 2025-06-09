#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TABLE_SIZE 50

typedef struct Student
{
	int usn;
	char name[100];
	char grade[10];
	struct Student* next;
} Student;

Student* hash_table[TABLE_SIZE] = {NULL};

unsigned int hash(int usn)
{
	return usn % TABLE_SIZE;
}

void insert(const int usn, const char *name, const char *grade)
{
	unsigned int index = hash(usn);
	Student* current = hash_table[index];

	while(current)
	{
		if(current->usn == usn)
		{
			printf("Student with usn %d already exists.\n", usn);
			return;
		}
		current = current->next;
	}
	
	Student* new_student = (Student* )malloc(sizeof(Student));
	new_student->usn = usn;
	strcpy(new_student->name, name);
	strcpy(new_student->grade, grade);
	new_student->next = hash_table[index];
	hash_table[index] = new_student;

	printf("Inserted student holding usn: %d.\n", usn);
}

void delete(int usn)
{
	unsigned int index = hash(usn);
	Student* current = hash_table[index];
	Student* prev = NULL;

	while(current)
	{
		if(current->usn == usn)
		{
			if(prev)
			{
				prev->next = current->next;
			}
			else
			{
				hash_table[index] = current->next;
			}
			free(current);

			printf("Deleted student holding usn: %d.\n", usn);
			return;
		}
		prev = current;
		current = current->next;
	}

	printf("Student holding usn %d not found.\n", usn);
}

void search(int usn)
{
	unsigned int index = hash(usn);
	Student* current = hash_table[index];

	while(current)
	{
		if(current->usn == usn)
		{
			printf("Student found!\n");
			printf("USN: %d\nName: %s\nGrade: %s\n", current->usn, current->name, current->grade);
			
			return;
		}
		current = current->next;
	}
	printf("Student holding USN %d not found.\n", usn);
}

void update(int usn, const char* name, const char* grade)
{
	unsigned int index = hash(usn);
	Student* current = hash_table[index];

	while(current)
	{
		if(current->usn == usn)
		{
			strcpy(current->name, name);
			strcpy(current->grade, grade);
			printf("Updated student holding USN %d.\n", usn);

			return;
		}
		current = current->next;
	}
	printf("Student not found.\nInsert student into the hash!\n");
}

void display()
{
	printf("\n*****STUDENT HASH TABLE*****\n\n");
	for(int i = 0; i < TABLE_SIZE; i++)
	{
		Student* current = hash_table[i];
		if(current)
		{
			printf("\nBucket %d:\n", i);
			while(current)
			{
				printf("USN: %d\nName: %s\nGrade: %s\n", current->usn, current->name, current->grade);
				current = current->next;
			}
		}
	}
}

int main()
{
	int choice = -1;
	int usn = -1;
	char name[64] = {0};
	char grade[32] = {0};

	while(1)
	{
		printf("\n***STUDENT HASH MENU***\n");
		printf("1. Insert Student\n");
		printf("2. Delete Student\n");
		printf("3. Search Student\n");
		printf("4. Update Student\n");
		printf("5. Display Students\n");
		printf("6. Exit!\n");

		printf("Enter your choice: ");
		scanf("%d", &choice);
		getchar();

		switch(choice)
		{
			case 1:
				printf("\nEnter USN: ");
				scanf("%d", &usn);
				getchar();

				printf("Enter Name: ");
				fgets(name, 100, stdin);
				name[strcspn(name, "\n")] = 0;
		
				printf("Enter Grade: ");
				scanf("%s", grade);
	
				insert(usn, name, grade);
				break;
			case 2:
				printf("\nEnter USN to delete: ");
				scanf("%d", &usn);

				delete(usn);
				break;
			case 3:
				printf("\nEnter USN to search: ");
				scanf("%d", &usn);

				search(usn);
				break;
			case 4:
				printf("\nEnter USN to update: ");
				scanf("%d", &usn);
				getchar();

				printf("Enter New Name: ");
				fgets(name, 100, stdin);
				name[strcspn(name, "\n")] = 0;

				printf("Enter New Grade: ");
				scanf("%s", grade);

				update(usn, name, grade);
				break;
			case 5:
				display();
				break;
			case 6:
				printf("Exiting..!!\n");
				exit(0);
			default:
				printf("Invalid Choice!\n");
		}
	}
	return 0;
}
