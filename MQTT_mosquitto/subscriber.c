#include <stdio.h>
#include <mosquitto.h>
#include <stdlib.h>
#include <string.h>
//#include "mqtt.h"

//#define BROKER_ADDRESS "192.168.85.149"
//#define PORT 1883
#define MQTT "mqtt.txt"
#define TOPIC "jessica/demo"
#define USERNAME "myuser"
#define PASSWORD "jessica"

char broker_address[100];
int port;
char username[20];
char password[20];

int get_next_line(FILE *fp, char *dest, size_t size, const char *field_name) {
        while (fgets(dest, size, fp)) {
                if (dest[0] == '#' || dest[0] == '\n') {
                        continue;
                }
                dest[strcspn(dest, "\n")] = 0;
                return 1;
        }

	fprintf(stderr, "Error: Missing or commented out: %s\n", field_name);  
        return 0;
}

void read_configuration()
{
        FILE *fp = fopen("mqtt.txt", "r");
        if (!fp)
        {
                perror("Failed to open config file");
                exit(1);
        }

        char port_line[100];

        if (!get_next_line(fp, broker_address, sizeof(broker_address), "broker address"))
        {
                exit(1);
        }

        if (!get_next_line(fp, port_line, sizeof(port_line), "port"))
        {
                exit(1);
        }
        port = atoi(port_line);

        if (!get_next_line(fp, username, sizeof(username), "username"))
        {
                exit(1);
        }

        if (!get_next_line(fp, password, sizeof(password), "password"))
        {
                exit(1);
        }

        fclose(fp);
}

/*int get_next_line() {
	FILE *fp = fopen("mqtt.txt", "r");
	if(!fp)
	{
		fprintf(stderr, "Failed to open config file!\n");
		exit(1);
	}
	char *dest[100];
	int size;
    	while (fgets(dest, size, fp)) {
        	if (dest[0] == '#' || dest[0] == '\n') {
            		continue;  
        	}
        	dest[strcspn(dest, "\n")] = 0;  
        	return 1;  
	}
    	return 0;  
}

void read_configuration() 
{
    	FILE *fp = fopen("mqtt.txt", "r");
    	if (!fp)
    	{
        	perror("Failed to open config file");
        	exit(1);
    	}

	get_next_line();
	char port_line[100];

    	if (fgets(broker_address, sizeof(broker_address), fp) == NULL) 
    	{
        	fprintf(stderr, "Error reading broker address\n");
        	exit(1);
    	}

    	if (fgets(port_line, sizeof(port_line), fp) == NULL) 
    	{
        	fprintf(stderr, "Error reading port\n");
        	exit(1);
    	}
	port = atoi(port_line);
    	
    	if (fgets(username, sizeof(username), fp) == NULL) 
    	{
        	fprintf(stderr, "Error reading username\n");
        	exit(1);
    	}

    	if (fgets( password, sizeof(password), fp) == NULL) 
	{
        	fprintf(stderr, "Error reading password\n");
        	exit(1);
    	}

    	fclose(fp);
}*/

void on_connect(struct mosquitto *mosq, void *userdata, int result) 
{
	if (result == MOSQ_ERR_SUCCESS) {
        printf("✅ Connected to broker successfully!\n");
        mosquitto_subscribe(mosq, NULL, TOPIC, 1);
    	} 
	else 
	{
        	fprintf(stderr, "❌ Connection failed: %s\n", mosquitto_strerror(result));
        	exit(1);
    	}
}

void on_message(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message) 
{	
	printf("📩 Received message: %s\n", (char *)message->payload);
}

int main() 
{
	read_configuration();
    	struct mosquitto *mosq;
    	int ret;
	
    	mosquitto_lib_init();

    	mosq = mosquitto_new(NULL, true, NULL);
    	if (!mosq) 
	{
        	fprintf(stderr, "❌ Failed to create Mosquitto instance\n");
        	return 1;
    	}

    	mosquitto_username_pw_set(mosq, username, password);

    	mosquitto_connect_callback_set(mosq, on_connect);
    	mosquitto_message_callback_set(mosq, on_message);
	
    	ret = mosquitto_connect(mosq, broker_address, port, 60);
    	if (ret != MOSQ_ERR_SUCCESS) 
	{
        	fprintf(stderr, "❌ Connection failed: %s\n", mosquitto_strerror(ret));
        	return 1;
    	}

    	printf("📡 Connecting to MQTT broker...\n");

    	mosquitto_loop_forever(mosq, -1, 1);

    	mosquitto_destroy(mosq);
    	mosquitto_lib_cleanup();

    	return 0;
}

