#include<stdio.h>
#include<stdlib.h>
#include "cJSON.h"

char *read_file(const char *filename)
{
	FILE *f = fopen(filename, "rb");
	if(!f)
	{
		perror("file not opened!");
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

int main()
{
	char *data1 = read_file("nested_json.json");
	char *data2 = read_file("nested_structure.json");
	if(!data1 || !data2)
	{
		printf("Error!");
		return 1;
	}

	cJSON *json1 = cJSON_Parse(data1);
	cJSON *json2 = cJSON_Parse(data2);
	free(data1);
	free(data2);

	if(!json1 || !json2)
	{
		printf("JSON parse error!.\n");
		return 1;
	}

	cJSON *arr1 = cJSON_GetObjectItem(json1, "student details");
	cJSON *arr2 = cJSON_GetObjectItem(json2, "student details");

	if(!cJSON_IsArray(arr1) || !cJSON_IsArray(arr2))
	{
		printf("Expected Arrays: \n");
		return 1;
	}

	int len2 = cJSON_GetArraySize(arr2);
    	for (int i = 0; i < len2; i++) 
	{
        	cJSON *item = cJSON_GetArrayItem(arr2, i);
        	cJSON_AddItemToArray(arr1, cJSON_Duplicate(item, 1));
    	}

	char *merged = cJSON_Print(json1);
    	printf("Merged JSON:\n%s\n", merged);

	free(merged);
    	cJSON_Delete(json1);
    	cJSON_Delete(json2);

	return 0;
}
