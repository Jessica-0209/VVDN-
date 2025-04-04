#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mosquitto.h>

#define MQTT_HOST "localhost"
#define MQTT_PORT 1883 
#define MQTT_TOPIC "test/topic"

int main()
{
    mosquitto_lib_init();

    struct mosquitto *mosq = mosquitto_new(NULL, true, NULL);
    if(!mosq)
    {
        printf("Failed to create Mosquitto client\n");
        return 1;
    }

    if(mosquitto_connect(mosq, MQTT_HOST, MQTT_PORT, 60))
    {
        printf("Could not connect to MQTT broker\n");
        return 1;
    }

    const char *message = "Hello from MQTT Publisher!";
    mosquitto_publish(mosq, NULL, MQTT_TOPIC, strlen(message), message, 1, false);

    printf("Message published: %s\n", message);

    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
    
    return 0;
}

