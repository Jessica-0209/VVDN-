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

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(1);
    }

    strncpy(ifr.ifr_name, "wlp44s0", IFNAMSIZ);  // your interface

    // Get current flags
    if (ioctl(sockfd, SIOCGIFFLAGS, &ifr) < 0) {
        perror("SIOCGIFFLAGS");
        close(sockfd);
        exit(1);
    }

    // Set the UP flag (without touching others)
    ifr.ifr_flags |= IFF_UP;

    // Set the updated flags
    if (ioctl(sockfd, SIOCSIFFLAGS, &ifr) < 0) {
        perror("SIOCSIFFLAGS");
        close(sockfd);
        exit(1);
    }

    printf("Interface %s brought up\n", ifr.ifr_name);

    close(sockfd);
    return 0;
}

