#include <stdio.h>
#include <mosquitto.h>
#include <stdlib.h>
#include <string.h>

#define MQTT "mqtt.txt"
#define TOPIC "jessica/demo"
//#define CLIENT_ID "jess_sub_01"
#define CA_FILE "/home/vvsa/VVDN-/MQTT_mosquitto/ssl/certs/ca.crt"

typedef struct
{
	char broker_address[100];
	int port;
	//char username[50];
	//char password[50];
} Config;

Config config = {
	.broker_address = "",
	.port = 0,
	//.username = "",
	//.password = ""
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
		/*else if (strcmp(key, "USERNAME") == 0) 
		{
            		strncpy(config.username, value, sizeof(config.username));
        	}	
       		else if (strcmp(key, "PASSWORD") == 0) 
		{
            		strncpy(config.password, value, sizeof(config.password));
        	}*/
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
    	/*if (strlen(config.username) == 0) 
    	{
        	fprintf(stderr, "Missing USERNAME in config file\n");
        	exit(1);
    	}
    	if (strlen(config.password) == 0) 
    	{
        	fprintf(stderr, "Missing PASSWORD in config file\n");
        	exit(1);
    	}*/
}

void on_connect(struct mosquitto *mosq, void *userdata, int result) 
{
	if (result == MOSQ_ERR_SUCCESS) {
        printf("✅ Connected to broker successfully!\n");
        mosquitto_subscribe(mosq, NULL, TOPIC, 1);
	printf("Subscribed to topic: %s\n", TOPIC);
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
    	struct mosquitto *mosq;
    	int ret;
	
    	mosquitto_lib_init();

    	mosq = mosquitto_new(NULL, true, NULL);
    	if (!mosq) 
	{
        	fprintf(stderr, "❌ Failed to create Mosquitto instance\n");
        	return 1;
    	}
	read_configuration("mqtt.txt");

	ret = mosquitto_tls_set(mosq, CA_FILE, NULL, NULL, NULL, NULL);
    	if (ret != MOSQ_ERR_SUCCESS) 
	{
        	fprintf(stderr, "❌ Failed to set TLS options: %s\n", mosquitto_strerror(ret));
        	return 1;
    	}
	mosquitto_tls_opts_set(mosq, 1, "tlsv1.2", NULL);
    	
	//mosquitto_username_pw_set(mosq, config.username, config.password);
    	mosquitto_connect_callback_set(mosq, on_connect);
    	mosquitto_message_callback_set(mosq, on_message);
	
    	ret = mosquitto_connect(mosq, config.broker_address, config.port, 60);
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
