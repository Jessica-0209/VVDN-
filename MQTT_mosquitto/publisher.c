#include <stdio.h>
#include <mosquitto.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BROKER_ADDRESS "localhost"
#define PORT 1883
#define TOPIC "secure/topic"
#define USERNAME "myuser"
#define PASSWORD "jessica"

void on_connect(struct mosquitto *mosq, void *userdata, int result) {
    if (result != 0) {
        printf("Connection failed\n");
        exit(1);
    }
    printf("Connected to broker\n");
}

int main() {

    struct mosquitto *mosq;
    mosquitto_lib_init();

    mosq = mosquitto_new(NULL, true, NULL);
    if (!mosq) {
        fprintf(stderr, "Failed to create Mosquitto instance\n");
        return 1;
    }

    mosquitto_username_pw_set(mosq, USERNAME, PASSWORD);
    mosquitto_connect_callback_set(mosq, on_connect);

    if (mosquitto_connect(mosq, BROKER_ADDRESS, PORT, 60) != MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "Failed to connect to broker\n");
        return 1;
    }

    char message[256];
    while (1) {

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

