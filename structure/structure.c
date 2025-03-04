#include<stdio.h>
#include<string.h>

//defining structure
struct Student
{
	char name[50];
	int age;
	float marks;
};

int main()
{
	struct Student s1 = {"Jessica", 21, 85.5}; //direct initialization

	struct Student s2;
	strcpy(s2.name, "Joanne");
	s2.age = 17;
	s2.marks = 95.8;

	printf("Student 1:\n");
	printf("Name: %s\n", s1.name);
	printf("Age: %d\n", s1.age);
	printf("Marks: %.2f\n", s1.marks);

	printf("\nStudent 2: \n");
	printf("Name: %s\n", s2.name);
        printf("Age: %d\n", s2.age);
        printf("Marks: %.2f\n", s2.marks);

	return 0;
}

