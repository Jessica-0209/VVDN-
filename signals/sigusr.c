/*#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handle_sigusr1(int sig) 
{
    	printf("SIGUSR1 received: Enabling DEBUG mode!\n");
}

void handle_sigusr2(int sig) 
{
    	printf("SIGUSR2 received: Disabling DEBUG mode!\n");
}

int main() 
{
    	signal(SIGUSR1, handle_sigusr1);
    	signal(SIGUSR2, handle_sigusr2);

    	printf("Process PID: %d\n", getpid());

    	while (1) 
	{
        	printf("Running...\n");
        	sleep(5);
    	}

    	return 0;
}
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

// Signal handler for the parent
void handle_sigusr1(int sig) {
    printf("Parent received SIGUSR1 from child!\n");
}

int main() {
    pid_t pid;

    // Register signal handler for SIGUSR1
    signal(SIGUSR1, handle_sigusr1);

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        sleep(1); // Give parent time to set up handler
        printf("Child sending SIGUSR1 to parent...\n");
        kill(getppid(), SIGUSR1); // Send signal to parent
        exit(0);
    } else {
        // Parent process
        pause(); // Wait for signal
        wait(NULL); // Wait for child to finish
    }

    return 0;
}

