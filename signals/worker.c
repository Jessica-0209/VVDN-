#include <stdio.h>
#include <unistd.h>

int main() 
{
    	while (1) 
    	{
        	printf("Worker running: PID %d\n", getpid());
        	sleep(2);
    	}
    	return 0;
}

