#include <stdio.h>
#include <stdlib.h>
#include <mosquitto.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#define MQTT_HOST "localhost"
#define MQTT_PORT 1883

void kill_processes()
{
    printf("Terminating all MQTT-related processes...\n");

    // Kill subscriber and publisher by name
    system("pkill -f subscriber");
    system("pkill -f publisher");

    // Optional: Kill Mosquitto broker itself (Only if you want to stop the broker too)
    // system("pkill -f mosquitto");
}

int main()
{
    printf("Initializing Mosquitto...\n");
    mosquitto_lib_init();

    struct mosquitto *mosq = mosquitto_new(NULL, true, NULL);
    if(!mosq)
    {
        printf("Failed to create Mosquitto client\n");
        return 1;
    }

    printf("Connecting to MQTT broker...\n");
    if(mosquitto_connect(mosq, MQTT_HOST, MQTT_PORT, 60))
    {
        printf("Could not connect to MQTT broker\n");
        return 1;
    }

    // Send proper MQTT DISCONNECT packet
    printf("Sending MQTT DISCONNECT packet...\n");
    mosquitto_disconnect(mosq);

    // Destroy Mosquitto instance
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    // Kill running processes
    kill_processes();

    printf("Disconnected from MQTT broker and terminated processes.\n");

    return 0;
}

