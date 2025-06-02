#include <stdio.h>
#include <stdlib.h>
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
    	char *json_array = read_file("json_array.json");
    	if (!json_array)
	{
		return 1;
	}

    	cJSON *root = cJSON_Parse(json_array);
    	if (!root) 
	{
        	printf("Parsing failed: %s\n", cJSON_GetErrorPtr());
        	free(json_array);
        	return 1;
    	}

	const char *key = "network details(wlp44s0)";
    	cJSON *network_array = cJSON_GetObjectItem(root, key);

    	if (cJSON_IsArray(network_array)) 
	{
        	int count = cJSON_GetArraySize(network_array);
        	printf("Found %d network entries:\n", count);

        	for (int i = 0; i < count; i++) 
		{
            		cJSON *entry = cJSON_GetArrayItem(network_array, i);
            		cJSON *ssid = cJSON_GetObjectItem(entry, "SSID");
            		cJSON *ip = cJSON_GetObjectItem(entry, "IP");
            		cJSON *connected = cJSON_GetObjectItem(entry, "connected");

            		printf("\nEntry %d:\n", i + 1);
            		if (cJSON_IsString(ssid))
			{	
				printf("  SSID: %s\n", ssid->valuestring);
			}
            
			if (cJSON_IsString(ip))
			{	
				printf("  IP: %s\n", ip->valuestring);
			}

            		if (cJSON_IsBool(connected))
			{	
				printf("  Connected: %s\n", cJSON_IsTrue(connected) ? "Yes" : "No");
			}
        	}
    	} 
	else 
	{
        	printf("Expected an array at key: %s\n", key);
    	}

    	cJSON_Delete(root);
    	free(json_array);
    
	return 0;
}
