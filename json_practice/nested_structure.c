#include<stdio.h>
#include<stdlib.h>
#include "cJSON.h"

char *read_file(const char *filename)
{
	FILE *f = fopen(filename, "rb");
	if(!f)
	{
		perror("File not opened!");
		return NULL;
	}

	fseek(f, 0, SEEK_END);
	long size = ftell(f);
	rewind(f);

	char *buffer = malloc(size + 1);
	if(!buffer)
	{
		fclose(f);
		return NULL;
	}

	fread(buffer, 1, size, f);
	buffer[size] = '\0';
	fclose(f);
	return buffer;

}

void print_skills(cJSON *skills_array)
{
	if(!cJSON_IsArray(skills_array))
	{
		return;
	}

	int skill_count  = cJSON_GetArraySize(skills_array);

	for (int i = 0; i < skill_count; i++)
	{
		cJSON *skill = cJSON_GetArrayItem(skills_array, i);
		if(cJSON_IsString(skill))
		{
			printf("%s", skill->valuestring);
			if(i < skill_count - 1)
			{
				printf(", ");
			}
		}
	}
}

void parse_students(cJSON *students)
{
	int student_count = cJSON_GetArraySize(students);
	for(int i = 0; i < student_count; i++)
	{
		cJSON *student = cJSON_GetArrayItem(students, i);
		cJSON *name = cJSON_GetObjectItem(student, "name");
		cJSON *class = cJSON_GetObjectItem(student, "class");
		cJSON *internships = cJSON_GetObjectItem(student, "internships");

		if(cJSON_IsString(name) && cJSON_IsString(class))
		{
			printf("Student Name: %s\n", name->valuestring);
			printf("Class: %s\n", class->valuestring);
		}

		if(cJSON_IsArray(internships))
		{
			printf("Internships:\n");
			int internship_count = cJSON_GetArraySize(internships);
			for(int j = 0; j < internship_count; j++)
			{
				cJSON *internship = cJSON_GetArrayItem(internships, j);
				cJSON *organization = cJSON_GetObjectItem(internship, "organization");
				cJSON *department = cJSON_GetObjectItem(internship, "department");
				cJSON *skills = cJSON_GetObjectItem(internship, "skills_gained");
				cJSON *duration = cJSON_GetObjectItem(internship, "duration");

				if(cJSON_IsString(organization))
				{
					printf(" -Organization: %s\n", organization->valuestring);
				}
				if(cJSON_IsString(department))
                                {
                                        printf(" -Department: %s\n", department->valuestring);
                                }
				if(cJSON_IsString(skills))
                                {
                                        printf(" -Skills: ");
					print_skills(skills);
					printf("\n");
                                }
				if(cJSON_IsString(duration))
                                {
                                        printf(" -Duration: %s\n\n", duration->valuestring);
                                }
			}
		}
		
		printf("\n");
	}
}

int main()
{
	char *nested_structure = read_file("nested_structure.json");
	if(!nested_structure)
	{
		return 1;
	}

	cJSON *root = cJSON_Parse(nested_structure);
	if(!root)
	{
		printf("Parsing failed: %s\n", cJSON_GetErrorPtr());
		free(nested_structure);
		return 1;
	}

	cJSON *students = cJSON_GetObjectItem(root, "student details");
	if(cJSON_IsArray(students))
	{
		parse_students(students);
	}
	else
	{
		printf("Not an array!\n");
	}

	cJSON_Delete(root);
	free(nested_structure);
	
	return 0;
}
