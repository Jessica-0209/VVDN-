#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>

void handle_signal(int sig)
{
        printf("Signal caught! Not dying!\n");
}

void seg_fault(int sig)
{
	printf("Segmentation fault!\n");
}

int main()
{
	int *p = NULL;

        signal(SIGINT, handle_signal);  //will sense ctrl+c and process will not terminate                kill -TERM <PID>
        signal(SIGTERM, handle_signal); //will sense term signal and process will not terminate           kill -KILL <PID>
        signal(SIGKILL, handle_signal); //will anyway kill the process...we cannot handle SIGKILL         
        signal(SIGSEGV, seg_fault);

	*p = 45; //causes segmentation fault(core dump)
	while(1)
        {
                printf("Process is running....PID: %d\n", getpid());
                sleep(2);
        }

        return 0;
}

