#include<stdio.h>
#include<stdlib.h>
#include "cJSON.h"

char *read_file(const char *filename)
{
	FILE *f = fopen(filename, "rb");
	if(!f)
	{
		perror("File open error!");
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
	const char *filename = "basic_json.json";

	char *basic_json = read_file(filename);
	if(!basic_json)
	{
		return 1;
	}

	cJSON *json = cJSON_Parse(basic_json);
	if(!json)
	{
		printf("JSON parsing failed: %s\n", cJSON_GetErrorPtr());
		free(basic_json);
		return 1;
	}

	cJSON *name = cJSON_GetObjectItemCaseSensitive(json, "name");
	cJSON *age = cJSON_GetObjectItemCaseSensitive(json, "age");
	cJSON *city = cJSON_GetObjectItemCaseSensitive(json, "city");

	printf("Parsed JSON!\n");

	if(cJSON_IsString(name))
	{
		printf("Name %s\n", name->valuestring);
	}

	if(cJSON_IsNumber(age))
        {
                printf("Age %d\n", age->valueint);
        }

	if(cJSON_IsString(city))
        {
                printf("City %s\n", city->valuestring);
        }

	cJSON_Delete(json);
	free(basic_json);
	
	return 0;
}
