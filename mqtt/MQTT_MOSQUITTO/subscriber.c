#include <stdio.h>
#include <stdlib.h>
#include <mosquitto.h>

#define MQTT_HOST "localhost"
#define MQTT_PORT 1883
#define MQTT_TOPIC "test/topic"

void on_connect(struct mosquitto *mosq, void *obj, int result)
{
    if(result)
    {
        printf("Failed to connect to MQTT broker!\n");
        exit(1);
    }
    printf("Connected to MQTT broker\n");
    
    mosquitto_subscribe(mosq, NULL, MQTT_TOPIC, 1);
}

void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message)
{
    printf("Received message on topic %s: %s\n", message->topic, (char *)message->payload);
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

    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_message_callback_set(mosq, on_message);

    if(mosquitto_connect(mosq, MQTT_HOST, MQTT_PORT, 60))
    {
        printf("Could not connect to MQTT broker\n");
        return 1;
    }

    mosquitto_loop_start(mosq);
    
    printf("Press Enter to exit...\n");
    getchar();

    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
    
    return 0;
}

