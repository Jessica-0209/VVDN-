#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handle_sighup(int sig) 
{
    	printf("Caught SIGHUP (Terminal disconnected or hangup)\n");
}

int main() 
{
    	signal(SIGHUP, handle_sighup);
    	while (1) 
    	{
        	sleep(2);
    	}
}

