#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

void handle_signal(int sig)
{
	switch(sig)
	{
		case SIGINT:
			printf("Caught SIGINT (Ctrl+C)!\n");
			break;
		case SIGTERM:
			printf("Caught SIGTERM (Termination)!\n");
			break;
		case SIGUSR1:
			printf("Caught SIGUSR1 (user-defined signal 1)!\n");
			break;
		default:
			printf("Signal caught: %d\n", sig);
	}
}

void daemonize()
{
	pid_t pid = fork();

	if(pid < 0)
	{
		exit(EXIT_FAILURE);
	}
	if(pid > 0)
	{
		exit(EXIT_SUCCESS);
	}

	umask(0);

	if(setsid < 0)
	{
		exit(EXIT_FAILURE);
	}
	if(chdir("/") < 0)
	{
		exit(EXIT_SUCCESS);
	}

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

int main()
{
	signal(SIGINT, handle_signal);
	signal(SIGTERM, handle_signal);
	signal(SIGUSR1, handle_signal);

	daemonize();

	FILE *log = fopen("/home/vvsa/VVDN-/signals/tmp/daemon_log.txt", "a+");
	if (log == NULL)
    	{
        	perror("Failed to open log file");
        	exit(EXIT_FAILURE);
    	}

	while(1)
	{
		fprintf(log, "Daemon is running....PID: %d\n", getpid());
		fflush(log);
		sleep(5);
	}

	fclose(log);

	return 0;
}
