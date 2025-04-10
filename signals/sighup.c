#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void handle_sighup(int sig)
{
        printf("Caught SIGHUP (hangup).....\n");

	printf("Current PID: %d\n", getpid());
    	sleep(1);
}

int main()
{        
        while (1)
	{
		signal(SIGHUP, handle_sighup);
                printf("Process is running...\n");
         
                kill(getpid(), SIGHUP);

		sleep(2);
	}

        return 0;
}

