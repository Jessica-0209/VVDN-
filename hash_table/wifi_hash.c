#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"cJSON.h"

#define TABLE_SIZE 101

typedef struct Wifi_Event
{
	char mac[24];
	char ssid[32];
	char event_type[64];
	char timestamp[32];
	struct Wifi_Event* next;
} Wifi_Event;

Wifi_Event* hash_table[TABLE_SIZE] = {NULL};

unsigned int hash(const char* str)
{
	unsigned long hash = 5381;
	int c;

	//converting each character of the MAC Address into ASCII to end up with a very big number, then doing mod
	while((c = *str++))
	{
		hash = ((hash << 5) + hash) + c;
	}

	return hash % TABLE_SIZE;
}

void insert(const char* mac, const char* ssid, const char* event_type, const char* timestamp)
{
	unsigned int index = hash(mac);
	Wifi_Event* current = hash_table[index];

	while(current)
	{
		if(strcmp(current->mac, mac) == 0)
		{
			printf("Device %s already exists!\n", mac);
			return;
		}

		current = current->next;
	}

	Wifi_Event* new_event = (Wifi_Event*)malloc(sizeof(Wifi_Event));
	strncpy(new_event->mac, mac, sizeof(new_event->mac));
	strncpy(new_event->ssid, ssid, sizeof(new_event->ssid));
	strncpy(new_event->event_type, event_type, sizeof(new_event->event_type));
	strncpy(new_event->timestamp, timestamp, sizeof(new_event->timestamp));

	new_event->next = hash_table[index];
	hash_table[index] = new_event;

	printf("Inserted new event for MAC %s\n.", mac);
}

void update(const char* mac, const char* ssid, const char* event_type, const char* timestamp)
{
	unsigned int index = hash(mac);
        Wifi_Event* current = hash_table[index];

	while(current)
	{
		if(strcmp(current->mac, mac) == 0)
		{
			strncpy(current->ssid, ssid, sizeof(current->ssid));
        		strncpy(current->event_type, event_type, sizeof(current->event_type));
        		strncpy(current->timestamp, timestamp, sizeof(current->timestamp));
			
			printf("Updated event for MAC %s\n.", mac);
			return;
		}
		current = current->next;
	}
	printf("Device %s not found!\n", mac);
}

void parse_and_insert(const char* json_str)
{
	cJSON* root = cJSON_Parse(json_str);
	if(!root)
	{
		printf("Invalid!\n");
		return;
	}

	cJSON* mac = cJSON_GetObjectItemCaseSensitive(root, "mac");
	cJSON* ssid = cJSON_GetObjectItemCaseSensitive(root, "ssid");
	cJSON* event_type = cJSON_GetObjectItemCaseSensitive(root, "event_type");
	cJSON* timestamp = cJSON_GetObjectItemCaseSensitive(root, "timestamp");

	if (cJSON_IsString(mac) && cJSON_IsString(ssid) && cJSON_IsString(event_type) && cJSON_IsString(timestamp))
	{
		insert(mac->valuestring, ssid->valuestring, event_type->valuestring, timestamp->valuestring);
	}
	else if (cJSON_IsString(mac))
	{
		update(mac->valuestring, ssid && cJSON_IsString(ssid) ? ssid->valuestring : NULL, event_type && cJSON_IsString(event_type) ? event_type->valuestring : NULL, timestamp && cJSON_IsString(timestamp) ? timestamp->valuestring : NULL);
	}
	else
	{
		printf("Missing fields in JSON\n");
	}

	cJSON_Delete(root);
}

void display()
{
	printf("\n*****WIFI EVENTS TABLE*****\n");
	for (int i = 0; i < TABLE_SIZE; i++) 
	{
        	Wifi_Event* current = hash_table[i];
        	if (current) 
		{
            		printf("\nBucket %d:\n", i);
            		while (current) 
	    		{
                		printf("  MAC: %s | SSID: %s | Event: %s | Time: %s\n", current->mac, current->ssid, current->event_type, current->timestamp);
                		current = current->next;
            		}
        	}
    	}
}

void free_table()
{
	for (int i = 0; i < TABLE_SIZE; i++) 
	{
        	Wifi_Event* current = hash_table[i];
        	while(current) 
		{
            		Wifi_Event* tmp = current;
            		current = current->next;
            		free(tmp);
        	}
        	hash_table[i] = NULL;
    	}
}

int main() 
{
    
	const char* json1 = "{\"mac\":\"00:11:22:33:44:55\",\"ssid\":\"TestNet\",\"event_type\":\"PROBE_REQ\",\"timestamp\":\"2025-06-09 11:00:00\"}";
    	const char* json2 = "{\"mac\":\"AA:BB:CC:DD:EE:FF\",\"ssid\":\"IoTLab\",\"event_type\":\"ASSOC_REQ\",\"timestamp\":\"2025-06-09 11:05:00\"}";
    	const char* json3 = "{\"mac\":\"00:11:22:33:44:55\",\"ssid\":\"TestNet\",\"event_type\":\"DISASSOC\",\"timestamp\":\"2025-06-09 11:10:00\"}";

    	parse_and_insert(json1);
    	parse_and_insert(json2);
    	parse_and_insert(json3);

    	display();

    	free_table();
    	return 0;
}
