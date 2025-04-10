#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void handle_sigint(int sig)
{
	printf("Caught signal interrupt(sigint)!\n");
}

int main()
{
	signal(SIGINT, handle_sigint);

	while(1)
	{
		printf("Press Ctrl+C to send SIGINT!\n");
		sleep(2);
	}
}
