#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_signal(int sig) 
{
    switch (sig) 
    {
        case SIGINT:
            printf("Caught SIGINT (Ctrl+C)\n");
            break;
        case SIGTERM:
            printf("Caught SIGTERM (Termination signal)\n");
            break;
        case SIGUSR1:
            printf("Caught SIGUSR1 (User-defined signal 1 for enabling debug log)\n");
            break;
	case SIGUSR2:
	    printf("Caught SIGUSR2 (for disabling debug log)\n");
	    break;
        default:
            printf("Caught signal: %d\n", sig);
    }
}

int main() 
{
    signal(SIGINT, handle_signal);   // Ctrl+C
    signal(SIGTERM, handle_signal);  // kill <pid>
    signal(SIGUSR1, handle_signal);  // kill -USR1 <pid>
    signal(SIGUSR2, handle_signal);

    printf("PID: %d\n", getpid());
    printf("Waiting for signals. Press Ctrl+C or send signals using kill.\n");
 
    while (1) 
    {
	   printf("Process running...PID: %d\n", getpid());
	   sleep(3);
    }
    return 0;
}
