#include <stdio.h>
#include <mosquitto.h>
#include <stdlib.h>

int main() {
    mosquitto_lib_init();

    // Force-disconnect by connecting with the same client ID as subscriber
    struct mosquitto *mosq = mosquitto_new("subscriber_client_id", true, NULL);
    if (!mosq || mosquitto_connect(mosq, "localhost", 1883, 60) != MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "Failed to initialize/connect.\n");
        return 1;
    }

    mosquitto_disconnect(mosq);  // Kills existing subscriber connection
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    // Ensure subscriber process is dead (Linux/macOS)
    system("pkill -f subscriber");
    printf("Subscriber disconnected and killed.\n");
    return 0;
}
