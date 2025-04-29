// ioctl_check.c
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>

int main() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct ifreq ifr;
    strncpy(ifr.ifr_name, "wlp44s0", IFNAMSIZ);

    if (ioctl(sock, SIOCGIFFLAGS, &ifr) == -1) {
        perror("ioctl");
        return 1;
    }

    if (ifr.ifr_flags & IFF_UP) {
        printf("wlp44s0 is UP\n");
    } else {
        printf("wlp44s0 is DOWN\n");
    }

    close(sock);
    return 0;
}

