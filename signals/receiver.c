#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_usr1(int sig) {
    printf("Received SIGUSR1\n");
}

void handle_usr2(int sig) {
    printf("Received SIGUSR2\n");
}

int main() {
    // Register signal handlers
    signal(SIGUSR1, handle_usr1);
    signal(SIGUSR2, handle_usr2);

    printf("Receiver process started with PID: %d\n", getpid());

    while (1) {
        // Wait for signals indefinitely
        pause();
    }

    return 0;
}

