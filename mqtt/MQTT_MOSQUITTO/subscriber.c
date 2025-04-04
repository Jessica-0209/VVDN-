#include <stdio.h>
#include <stdlib.h>
#include <mosquitto.h>

#define MQTT_HOST "localhost"
#define MQTT_PORT 1883
#define MQTT_TOPIC "test/topic"

void on_message(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *msg)
{
    printf("Received message on topic %s: %s\n", msg->topic, (char *)msg->payload);
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

    mosquitto_loop_forever(mosq, -1, 1);

    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
    return 0;
}

