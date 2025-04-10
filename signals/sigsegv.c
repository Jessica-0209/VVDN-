#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

volatile sig_atomic_t segfault = 0;

void handle_sigsegv(int sig) 
{
	printf("Caught SIGSEGV (Invalid memory access)\n");
    	segfault = 1;
	exit(1);
}

int main() 
{
    	signal(SIGSEGV, handle_sigsegv);
    	//int a = 10;
	int *ptr = NULL;

    	//ptr = &a; 
	*ptr = 10; // Causes segmentation fault
	
	if(!segfault)
	{
		printf("Code is clear. No segmentation fault!\n");
	}

    	return 0;
}

