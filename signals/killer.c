#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() 
{
    	printf("This is the killer program. Waiting 5 seconds...\n");
    	sleep(5);  

    	printf("Now executing killall on 'worker'\n");
    	int status = system("killall worker");

    	if (status == -1) 
    	{
        	perror("system call failed");
    	} 	
    	else 
    	{
        	printf("killall command executed with exit status: %d\n", WEXITSTATUS(status));
    	}
	
    	return 0;
}

