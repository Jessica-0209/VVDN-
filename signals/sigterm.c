#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handle_sigterm(int sig) 
{
    	printf("Caught SIGTERM. Gracefully terminating...\n");
}

int main() 
{
    	signal(SIGTERM, handle_sigterm);
    	while (1) 
	{
        	printf("Waiting for SIGTERM (kill command)...\n");
        	sleep(2);
    	}
}

