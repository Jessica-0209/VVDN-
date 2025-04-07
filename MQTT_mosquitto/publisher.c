#include <stdio.h>
#include <mosquitto.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//#define BROKER_ADDRESS "192.168.85.149"
//#define PORT 1883
#define MQTT "mqtt.txt"
#define TOPIC "jessica/demo"

char broker_address[100];
int port;
char username[20];
char password[20];

int get_next_line(FILE *fp, char *dest, size_t size) {
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

        char port_line[100];

        if (!get_next_line(fp, broker_address, sizeof(broker_address)))
        {
                fprintf(stderr, "Error reading broker address\n");
                exit(1);
        }

        if (!get_next_line(fp, port_line, sizeof(port_line)))
        {
                fprintf(stderr, "Error reading port\n");
                exit(1);
        }
        port = atoi(port_line);

        if (!get_next_line(fp, username, sizeof(username)))
        {
                fprintf(stderr, "Error reading username\n");
                exit(1);
        }

        if (!get_next_line(fp, password, sizeof(password)))
        {
                fprintf(stderr, "Error reading password\n");
                exit(1);
        }

        fclose(fp);
}

void on_connect(struct mosquitto *mosq, void *userdata, int result) {
    if (result != 0) {
        printf("Connection failed\n");
        exit(1);
    }
    printf("Connected to broker\n");
}

int main() {
	
	read_configuration();
    	struct mosquitto *mosq;
    	mosquitto_lib_init();

    	mosq = mosquitto_new(NULL, true, NULL);
    	if (!mosq) 
	{
		fprintf(stderr, "Failed to create Mosquitto instance\n");
        	return 1;
    	}

    	mosquitto_username_pw_set(mosq, username, password);
    	mosquitto_connect_callback_set(mosq, on_connect);

    	if (mosquitto_connect(mosq, broker_address, port, 60) != MOSQ_ERR_SUCCESS) 
	{	
		fprintf(stderr, "Failed to connect to broker\n");
        	return 1;
    	}

    	char message[256];
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

