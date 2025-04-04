#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For sleep()
#include <mosquitto.h>

#define MQTT_HOST "localhost"
#define MQTT_PORT 1883
#define MQTT_TOPIC "secure/topic"
#define MQTT_USER "myuser"
#define MQTT_PASS "mypassword"

int main()
{
    mosquitto_lib_init();

    struct mosquitto *mosq = mosquitto_new(NULL, true, NULL);
    if (!mosq)
    {
        printf("Failed to create Mosquitto client\n");
        return 1;
    }

    // Set authentication details
    mosquitto_username_pw_set(mosq, MQTT_USER, MQTT_PASS);

    // Connect to MQTT broker
    if (mosquitto_connect(mosq, MQTT_HOST, MQTT_PORT, 60))
    {
        printf("Could not connect to MQTT broker (Check username/password)\n");
        return 1;
    }

    // Publish a message
    const char *message = "Hello, Secure MQTT!";
    mosquitto_publish(mosq, NULL, MQTT_TOPIC, strlen(message), message, 1, false);

    printf("Message published: %s\n", message);

    // Add delay to ensure message delivery
    sleep(2);

    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return 0;
}

