#include <stdio.h>
#include <mosquitto.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//#define BROKER_ADDRESS "192.168.85.149"
//#define PORT 1883
#define MQTT "mqtt.txt"
#define TOPIC "jessica/demo"

typedef struct
{
        char broker_address[100];
        int port;
        char username[50];
        char password[50];
} Config;

Config config = {
        .broker_address = "",
        .port = 0,
        .username = "",
        .password = ""
};

void read_configuration(const char *filename) {
        FILE *fp = fopen(filename, "r");
        if (!fp)
        {
                perror("Failed to open config file");
                exit(1);
        }

        char line[256] = {0};
        while (fgets(line, sizeof(line), fp)) {
                if (line[0] == '#' || line[0] == '\n')
                {
                        continue;
                }

                line[strcspn(line, "\n")] = 0; // remove newline

                char *key = strtok(line, "=");
                char *value = strtok(NULL, "=");

                if (!key || !value)
                {
                        continue;
                }

                if (strcmp(key, "BROKER_ADDRESS") == 0)
                {
                        strncpy(config.broker_address, value, sizeof(config.broker_address));
                }
                else if (strcmp(key, "PORT") == 0)
                {
                        config.port = atoi(value);
                }
                else if (strcmp(key, "USERNAME") == 0)
                {
                        strncpy(config.username, value, sizeof(config.username));
                }
                else if (strcmp(key, "PASSWORD") == 0)
                {
                        strncpy(config.password, value, sizeof(config.password));
                }
        }

        fclose(fp);


        if (strlen(config.broker_address) == 0)
        {
                fprintf(stderr, "Missing BROKER_ADDRESS in config file\n");
                exit(1);
        }
        if (config.port == 0)
        {
                fprintf(stderr, "Missing or invalid BROKER_PORT in config file\n");
                exit(1);
        }
        if (strlen(config.username) == 0)
        {
                fprintf(stderr, "Missing USERNAME in config file\n");
                exit(1);
        }
        if (strlen(config.password) == 0)
        {
                fprintf(stderr, "Missing PASSWORD in config file\n");
                exit(1);
        }
}

void on_connect(struct mosquitto *mosq, void *userdata, int result) 
{
    	if (result != 0) 
	{
        	printf("Connection failed\n");
        	exit(1);
    	}
    	printf("Connected to broker\n");
}

int main() 
{
    	struct mosquitto *mosq;
    	mosquitto_lib_init();

    	mosq = mosquitto_new(NULL, true, NULL);
    	if (!mosq) 
	{
		fprintf(stderr, "Failed to create Mosquitto instance\n");
        	return 1;
    	}
	read_configuration("mqtt.txt");

    	mosquitto_username_pw_set(mosq, config.username, config.password);
    	mosquitto_connect_callback_set(mosq, on_connect);
    	if (mosquitto_connect(mosq, config.broker_address, config.port, 60) != MOSQ_ERR_SUCCESS) 
	{	
		fprintf(stderr, "Failed to connect to broker\n");
        	return 1;
    	}

    	char message[256] = {0};
    	while (1) 
	{
        	printf("Enter message to send: ");
        	fgets(message, sizeof(message), stdin);
        	message[strcspn(message, "\n")] = 0;

        	mosquitto_publish(mosq, NULL, TOPIC, strlen(message), message, 1, false);
        	printf("Message sent: %s\n", message);
    	}
    	mosquitto_destroy(mosq);
    	mosquitto_lib_cleanup();
    	return 0;
}
