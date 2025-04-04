#include <stdio.h>
#include <string.h>
#include <mosquitto.h>

#define MQTT_HOST "localhost"
#define MQTT_PORT 1883
#define MQTT_TOPIC "test/topic"

int main() {
    mosquitto_lib_init();
    struct mosquitto *mosq = mosquitto_new(NULL, true, NULL);

    if (!mosq || mosquitto_connect(mosq, MQTT_HOST, MQTT_PORT, 60) != MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "Failed to initialize/connect.\n");
        return 1;
    }

    const char *msg = "Hello from publisher!";
    mosquitto_publish(mosq, NULL, MQTT_TOPIC, strlen(msg), msg, 1, false);
    printf("Published: %s\n", msg);


    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
    return 0;
}
