#include <stdio.h>
#include <mosquitto.h>
#include <signal.h>

#define MQTT_HOST "localhost"
#define MQTT_PORT 1883
#define MQTT_TOPIC "test/topic"

volatile sig_atomic_t running = 1;

void on_message(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *msg) {
    if (msg->payloadlen) {
        printf("Received: %s\n", (char *)msg->payload);
    }
}

int main() {
    mosquitto_lib_init();
    struct mosquitto *mosq = mosquitto_new("subscriber_client_id", true, NULL);

    mosquitto_message_callback_set(mosq, on_message);
    if (mosquitto_connect(mosq, MQTT_HOST, MQTT_PORT, 60) != MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "Failed to connect.\n");
        return 1;
    }

    mosquitto_subscribe(mosq, NULL, MQTT_TOPIC, 1);
    printf("Subscriber running. Press Ctrl+C to exit.\n");

    while (running) {
        mosquitto_loop(mosq, -1, 1);
    }

    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
    return 0;
}
