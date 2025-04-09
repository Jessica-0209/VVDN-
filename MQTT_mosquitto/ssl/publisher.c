#include<stdio.h>
#include<mosquitto.h>
#include<stdlib.h>
#include<signal.h>
#include<stdbool.h>
#include<string.h>
#include<unistd.h>

#define MQTT "mqtt.txt"
#define TOPIC "jessica/demo"
#define CA_FILE "/home/vvsa/VVDN-/MQTT_mosquitto/ssl/certs/ca.crt"

volatile bool keep_running = true;
int connected = 0;

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

int read_configuration(const char *filename) 
{
        FILE *fp = fopen(filename, "r");
        if (!fp)
        {
                perror("Failed to open config file");
                return 0;
        }

        char line[256] = {0};
        while (fgets(line, sizeof(line), fp)) 
	{
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
                return 0;
        }
        if (config.port == 0)
        {
                fprintf(stderr, "Missing or invalid BROKER_PORT in config file\n");
                return 0;
        }
        if (strlen(config.username) == 0)
        {
                fprintf(stderr, "Missing USERNAME in config file\n");
                return 0;
        }
        if (strlen(config.password) == 0)
        {
                fprintf(stderr, "Missing PASSWORD in config file\n");
                return 0;
        }
	return 1;
}

void on_connect(struct mosquitto *mosq, void *userdata, int result) 
{
    	if(result == 0)
	{
		printf("✅ Connected successfully to broker!\n");
		connected = 1;
	} 
	else 
	{
       		printf("❌ Failed to connect, return code: %d\n", result);
    	}
}

void handle_sigint(int sig)
{
	printf("\n🔁 Ctrl+C pressed. Ignoring... Process will continue running.\n");
}

int main() 
{
    	struct mosquitto *mosq;
	int rc;
	//signal(SIGINT, handle_sigint);

	rc = mosquitto_lib_init();
	if(rc != MOSQ_ERR_SUCCESS) 
	{
    		fprintf(stderr, "❌ Failed to initialize Mosquitto library\n");
    		return 1;
	}

    	mosq = mosquitto_new(NULL, true, NULL);
    	if (!mosq) 
	{
		fprintf(stderr, "Failed to create Mosquitto instance\n");
        	return 1;
    	}

	if (!read_configuration("mqtt.txt")) 
	{
    		fprintf(stderr, "Configuration loading failed.\n");
    		exit(1);
	}

    	mosquitto_username_pw_set(mosq, config.username, config.password);
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
	while(!connected)
	{
	
	}

    	char message[256] = {0};
    	while (keep_running) 
	{
        	printf("Enter message to send: ");
    		while (fgets(message, sizeof(message), stdin))
    		{
        		message[strcspn(message, "\n")] = 0;

        		if (strcmp(message, "exit") == 0) 
			{
            			printf("👋 Exit command received. Shutting down...\n");
            			exit(0);
            			break;
        		}

			if (strlen(message) > 0) 
			{
          			break;
        		}
        		else 
			{
            			fprintf(stderr, "Invalid! Enter valid message!\n");
        		}
		}

		if (!keep_running) 
		{
        		break;
    		}

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
