#include <stdio.h>
#include <mosquitto.h>
#include <stdlib.h>
#include <string.h>

#define BROKER_ADDRESS "localhost"
#define PORT 1883
#define TOPIC "secure/topic"
#define USERNAME "myuser"
#define PASSWORD "jessica"

void on_connect(struct mosquitto *mosq, void *userdata, int result) {
    if (result == MOSQ_ERR_SUCCESS) {
        printf("✅ Connected to broker successfully!\n");
        mosquitto_subscribe(mosq, NULL, TOPIC, 1);
    } else {
        fprintf(stderr, "❌ Connection failed: %s\n", mosquitto_strerror(result));
        exit(1);
    }
}

void on_message(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message) {
    printf("📩 Received message: %s\n", (char *)message->payload);
}

int main() {
    struct mosquitto *mosq;
    int ret;

    mosquitto_lib_init();

    mosq = mosquitto_new(NULL, true, NULL);
    if (!mosq) {
        fprintf(stderr, "❌ Failed to create Mosquitto instance\n");
        return 1;
    }

    // Set username and password before connecting
    mosquitto_username_pw_set(mosq, USERNAME, PASSWORD);

    // Set connection and message callbacks
    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_message_callback_set(mosq, on_message);

    // Try to connect to the broker
    ret = mosquitto_connect(mosq, BROKER_ADDRESS, PORT, 60);
    if (ret != MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "❌ Connection failed: %s\n", mosquitto_strerror(ret));
        return 1;
    }

    printf("📡 Connecting to MQTT broker...\n");

    // Keep listening for messages
    mosquitto_loop_forever(mosq, -1, 1);

    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return 0;
}

