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

void print_array(cJSON *array)
{
	int size = cJSON_GetArraySize(array);
	for(int i = 0; i < size; i++)
	{
		cJSON *item = cJSON_GetArrayItem(array, i);
		if(cJSON_IsString(item))
		{
			printf("  - %s\n", item->valuestring);
		}
	}
}

int main()
{
	char *nested_json = read_file("nested_json.json");
	if(!nested_json)
	{
		return 1;
	}

	cJSON *root = cJSON_Parse(nested_json);
	if(!root)
	{
		printf("Parsing failed: %s\n", cJSON_GetErrorPtr());
		free(nested_json);
		return 1;
	}

	cJSON *student = cJSON_GetObjectItem(root, "student");
	if (student) {
        	cJSON *name = cJSON_GetObjectItem(student, "name");
        	cJSON *course = cJSON_GetObjectItem(student, "course");
        	cJSON *internship = cJSON_GetObjectItem(student, "internship");
        	cJSON *skills = cJSON_GetObjectItem(student, "skills");

        	printf("Student Info:\n\n");
        	if (cJSON_IsString(name))
		{
			printf("Name: %s\n", name->valuestring);
		}

        	if (cJSON_IsString(course))
		{
			printf("Course: %s\n", course->valuestring);
		}

        	if (cJSON_IsString(internship))
		{
			printf("Internship: %s\n", internship->valuestring);
		}

        	if (skills) 
		{
            		printf("Skills:\n");
			
			cJSON *prog_langs = cJSON_GetObjectItem(skills, "programming languages");
            		cJSON *net_concepts = cJSON_GetObjectItem(skills, "networking concepts");

            		if (prog_langs && cJSON_IsArray(prog_langs)) 
			{
                		printf(" Programming Languages:\n");
                		print_array(prog_langs);
            		}

            		if (net_concepts && cJSON_IsArray(net_concepts)) 
			{
                		printf(" Networking Concepts:\n");
                		print_array(net_concepts);
            		
			}
		}

	}

	cJSON_Delete(root);
	free(nested_json);

	return 0;
}
