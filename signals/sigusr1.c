// receiver.c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigusr1(int sig) {
    printf("Received SIGUSR1! Starting another process...\n"); 
    
    execl("/home/vvsa/VVDN-/signals/tmp", "ls", NULL);

    perror("execl failed"); //if execl fails
    exit(1);
}

void handle_sigusr2(int sig) 
{
    	printf("Received SIGUSR2! Saving logs...\n");
    	
	FILE *log_file = fopen("process_logs.txt", "a");
    	if (log_file) 
    	{
        	fprintf(log_file, "Log entry: Process with PID %d received SIGUSR2\n", getpid());
        	fclose(log_file);
        	printf("Logs saved successfully.\n");
    	}	 
    	else 
    	{
        	perror("Error saving logs");
    	}
}

int main() {
    signal(SIGUSR1, handle_sigusr1);
    
    printf("Receiver running. PID: %d\n", getpid());
    while (1) {
        pause();  // Wait for signal
    }

    return 0;
}

