#include<stdio.h>

typedef struct
{
	char name[14];
	int age;
	float weight;
	int roll_no;
} student_info;

int main()
{
	student_info ram_info;
	
	printf("Size of structure: %lu\n\n", sizeof(ram_info));

	return 0;
}
