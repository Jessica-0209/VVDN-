#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void handle_signal(int sig)
{
    	if (sig == SIGUSR1)
    	{
        	printf("Child process received SIGUSR1! Resuming now...\n");
    	}
}

int main()
{
    	pid_t pid = fork();

    	if (pid < 0)
    	{
        	perror("fork failed");
        	exit(1);
    	}

    	if (pid == 0)
    	{
        	printf("Child process started. PID: %d\n", getpid());

                signal(SIGUSR1, handle_signal);

                while (1)
        	{
            		printf("Child is now paused, waiting for SIGUSR1...\n");
            		pause(); // Wait for SIGUSR1 to continue
            		printf("Child process is paused again.\n");
        	}

        	exit(0);
    	}
    	else
    	{
                printf("Parent process started. PID: %d\n", getpid());
        	printf("Child PID is %d\n", pid);

                wait(NULL);
        	printf("Parent: Child exited!\n");
    	}

    	return 0;
}

