#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mosquitto.h>

void on_message(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message)
{
    	if (message->payloadlen)
    	{
        	printf("Received on topic %s: %s\n", message->topic, (char *)message->payload);

        	// Send acknowledgment
        	const char *ack = "Received scan report.";
        	mosquitto_publish(mosq, NULL, "scan/ack", strlen(ack), ack, 0, false);
    	}
}

int main()
{
    	mosquitto_lib_init();

    	struct mosquitto *mosq = mosquitto_new("subscriber", true, NULL);
    	if (!mosq)
    	{
        	fprintf(stderr, "Failed to create Mosquitto instance.\n");
        	return 1;
    	}

    	mosquitto_username_pw_set(mosq, "newuser", "mqtt");
    	mosquitto_message_callback_set(mosq, on_message);

    	if (mosquitto_connect(mosq, "localhost", 1883, 60) != MOSQ_ERR_SUCCESS)
    	{
        	fprintf(stderr, "Failed to connect to broker.\n");
        	mosquitto_destroy(mosq);
        	return 1;
    	}

    	mosquitto_subscribe(mosq, NULL, "scan/report/wifi", 0);

    	mosquitto_loop_forever(mosq, -1, 1);

    	mosquitto_destroy(mosq);
    	mosquitto_lib_cleanup();

    	return 0;
}

