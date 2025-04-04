#include <stdio.h>
#include <stdlib.h>
#include <mosquitto.h>
#include<unistd.h>

#define MQTT_HOST "localhost"
#define MQTT_PORT 1883
#define MQTT_TOPIC "secure/topic"
#define MQTT_USER "myuser"
#define MQTT_PASS "mypassword"

// Callback when the client disconnects
void disconnect_callback(struct mosquitto *mosq, void *userdata, int rc)
{
    if (rc)
    {
        printf("Unexpected disconnection! Reconnecting...\n");
        mosquitto_reconnect(mosq);
    }
}

// Callback when a message is received
void message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message)
{
    printf("Received Message: %s\n", (char *)message->payload);
}

int main()
{
    mosquitto_lib_init();

    struct mosquitto *mosq = mosquitto_new(NULL, true, NULL);
    if (!mosq)
    {
        printf("Failed to create Mosquitto client\n");
        return 1;
    }

    // Set authentication
    mosquitto_username_pw_set(mosq, MQTT_USER, MQTT_PASS);

    // Set callbacks
    mosquitto_message_callback_set(mosq, message_callback);
    mosquitto_disconnect_callback_set(mosq, disconnect_callback);

    // Connect to MQTT broker
    if (mosquitto_connect(mosq, MQTT_HOST, MQTT_PORT, 60))
    {
        printf("Could not connect to MQTT broker (Check username/password)\n");
        return 1;
    }

    // Subscribe to the topic
    mosquitto_subscribe(mosq, NULL, MQTT_TOPIC, 1);
    printf("Subscribed to topic: %s\n", MQTT_TOPIC);

    // Start the loop in a separate thread (Non-blocking)
    mosquitto_loop_start(mosq);

    // Keep the main program running
    while (1)
    {
        sleep(5); // Keep alive
    }

    // Cleanup
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return 0;
}

