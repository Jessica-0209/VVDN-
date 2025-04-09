#include <stdio.h>
#include <mosquitto.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MQTT "mqtt.txt"
#define TOPIC "jessica/demo"
#define CA_FILE "/home/vvsa/VVDN-/MQTT_mosquitto/ssl/certs/ca.crt"
//#define CERT_FILE "/home/vvsa/VVDN-/MQTT_mosquitto/ssl/certs/server.crt"
//#define KEY_FILE "/home/vvsa/VVDN-/MQTT_mosquitto/ssl/certs/server.key"

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

    	//mosquitto_username_pw_set(mosq, config.username, config.password);
    	mosquitto_connect_callback_set(mosq, on_connect);

	int ret = mosquitto_tls_set(mosq, CA_FILE, NULL, NULL, NULL, NULL);
    	if (ret != MOSQ_ERR_SUCCESS) 
	{
        	fprintf(stderr, "❌ Failed to configure TLS: %s\n", mosquitto_strerror(ret));
        	return 1;
    	}

    	if (mosquitto_connect(mosq, config.broker_address, config.port, 60) != MOSQ_ERR_SUCCESS) 
	{	
		fprintf(stderr, "Failed to connect to broker\n");
        	return 1;
    	}

	mosquitto_loop_start(mosq);
    	char message[256] = {0};
    	while (1) 
	{
        	printf("Enter message to send: ");
        	fgets(message, sizeof(message), stdin);
        	message[strcspn(message, "\n")] = 0;

        	int rc = mosquitto_publish(mosq, NULL, TOPIC, strlen(message), message, 1, false);
		if(rc == MOSQ_ERR_SUCCESS) 
		{
    			printf("✅ Message sent: %s\n", message);
		} 
		else 
		{
    			printf("❌ Failed to publish message: %s\n", mosquitto_strerror(rc));
		}

    	}
	sleep(1);
    	mosquitto_loop_stop(mosq, false);
    	mosquitto_disconnect(mosq);

    	mosquitto_destroy(mosq);
    	mosquitto_lib_cleanup();
    	return 0;
}
