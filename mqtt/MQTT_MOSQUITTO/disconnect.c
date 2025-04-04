#include <stdio.h>
#include <stdlib.h>
#include <mosquitto.h>
#include <unistd.h>  // For fork() and exec()
#include <signal.h>  // For kill()

int main() {
    mosquitto_lib_init();

    struct mosquitto *mosq = mosquitto_new(NULL, true, NULL);
    if (!mosq) {
        fprintf(stderr, "Error: Failed to create MQTT client.\n");
        return 1;
    }

    // Connect to broker
    /*if (mosquitto_connect(mosq, "localhost", 1883, 60) != MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "Error: Could not connect to broker.\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return 1;
    }*/

  
    mosquitto_disconnect(mosq);
    printf("Sent DISCONNECT packet.\n");

    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    system("pkill -f publisher");  // Kill publisher if running
    system("pkill -f subscriber"); // Kill subscriber if running

    return 0;
}
