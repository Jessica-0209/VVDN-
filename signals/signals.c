#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>

void handle_signal(int sig)
{
	printf("Signal caught! Not dying!\n");
}

int main()
{
	signal(SIGINT, handle_signal);  //will sense ctrl+c and process will not terminate                kill -TERM <PID>
	signal(SIGTERM, handle_signal); //will sense term signal and process will not terminate           kill -KILL <PID>
	signal(SIGKILL, handle_signal); //will anyway kill the process...we cannot handle SIGKILL         
	while(1)
	{
		printf("Process is running....PID: %d\n", getpid());
		sleep(2);
	}

	return 0;
}
