#include<stdio.h>
#include <sys/types.h>
#include <signal.h>

int main() 
{
    pid_t pid;

    printf("Enter the PID of the target process: ");
    scanf("%d", &pid);

    int result = kill(pid, SIGTERM);
    
    if (result == 0) 
    {
        printf("Signal successfully sent.\n");
    }
    else 
    {
        printf("Failed to send signal.\n");
    }
    
    return 0;
}
