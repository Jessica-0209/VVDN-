#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main() {
    pid_t pid;
    printf("Enter PID of the receiver process: ");
    scanf("%d", &pid);

    while (1) {
        // Send SIGUSR1 signal
        printf("Sending SIGUSR1...\n");
        kill(pid, SIGUSR1);
        sleep(1);

        // Send SIGUSR2 signal
        printf("Sending SIGUSR2...\n");
        kill(pid, SIGUSR2);
        sleep(1);
    }

    return 0;
}

