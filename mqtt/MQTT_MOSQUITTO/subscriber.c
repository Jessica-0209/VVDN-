#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mosquitto.h>

#define MQTT_HOST "localhost"
#define MQTT_PORT 1883
#define MQTT_TOPIC "test/topic"
#define SHUTDOWN_MESSAGE "shutdown"

int running = 1;

void on_message(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *msg)
{
    char *payload = (char *)msg->payload;
    printf("Received message on topic %s: %s\n", msg->topic, payload);

    if(strcmp(payload, SHUTDOWN_MESSAGE) == 0)
    {
        printf("Shutdown command received. Disconnecting and exiting...\n");
        mosquitto_disconnect(mosq);  // Gracefully disconnect
        running = 0;
    }
}

int main()
{
    mosquitto_lib_init();

    struct mosquitto *mosq = mosquitto_new(NULL, true, NULL);
    if(!mosq)
    {
        printf("Failed to create Mosquitto client\n");
        return 1;
    }

    mosquitto_message_callback_set(mosq, on_message);

    if(mosquitto_connect(mosq, MQTT_HOST, MQTT_PORT, 60))
    {
        printf("Could not connect to MQTT broker\n");
        return 1;
    }

    mosquitto_subscribe(mosq, NULL, MQTT_TOPIC, 1);
    printf("Connected to MQTT broker, subscribed to topic: %s\n", MQTT_TOPIC);

    while(running)
    {
        mosquitto_loop(mosq, -1, 1);
    }

    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
    return 0;
}

