#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <sys/socket.h>

int main() {
    int sockfd;
    struct ifreq ifr;

    // Create a socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(1);
    }

    // Specify the interface name
    strncpy(ifr.ifr_name, "wlp44s0", IFNAMSIZ);  // Change interface name if needed

    // Get current flags
    if (ioctl(sockfd, SIOCGIFFLAGS, &ifr) < 0) {
        perror("SIOCGIFFLAGS");
        close(sockfd);
        exit(1);
    }

    // Clear the UP flag
    ifr.ifr_flags &= ~IFF_UP;

    // Set the updated flags
    if (ioctl(sockfd, SIOCSIFFLAGS, &ifr) < 0) {
        perror("SIOCSIFFLAGS");
        close(sockfd);
        exit(1);
    }

    printf("Interface %s brought down\n", ifr.ifr_name);

    close(sockfd);
    return 0;
}

