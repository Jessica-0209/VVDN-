/*#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <linux/if.h>
#include <linux/sockios.h>

int main() {
    int sockfd;
    struct ifconf ifc;
    struct ifreq ifr[50];
    int interfaces, i;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(1);
    }

    ifc.ifc_len = sizeof(ifr);
    ifc.ifc_req = ifr;

    if (ioctl(sockfd, SIOCGIFCONF, &ifc) == -1) {
        perror("SIOCGIFCONF");
        close(sockfd);
        exit(1);
    }

    interfaces = ifc.ifc_len / sizeof(struct ifreq);

    printf("All network interfaces:\n\n");

    for (i = 0; i < interfaces; i++) {
        struct ifreq *item = &ifr[i];

        printf("Interface: %s\n", item->ifr_name);

        // Get Flags
        struct ifreq flags_req;
        strcpy(flags_req.ifr_name, item->ifr_name);
        if (ioctl(sockfd, SIOCGIFFLAGS, &flags_req) == 0) {
            printf("  Flags: ");
            short flags = flags_req.ifr_flags;
            if (flags & IFF_UP) printf("UP ");
            else printf("DOWN ");
            if (flags & IFF_BROADCAST) printf("BROADCAST ");
            if (flags & IFF_LOOPBACK) printf("LOOPBACK ");
            if (flags & IFF_RUNNING) printf("RUNNING ");
            if (flags & IFF_MULTICAST) printf("MULTICAST ");
            printf("\n");
        }

        // Get IP Address
        struct ifreq ip_req;
        strcpy(ip_req.ifr_name, item->ifr_name);
        if (ioctl(sockfd, SIOCGIFADDR, &ip_req) == 0) {
            struct sockaddr_in* ipaddr = (struct sockaddr_in*)&ip_req.ifr_addr;
            printf("  IP Address: %s\n", inet_ntoa(ipaddr->sin_addr));
        } else {
            printf("  IP Address: N/A\n");
        }

        // Get Netmask
        struct ifreq netmask_req;
        strcpy(netmask_req.ifr_name, item->ifr_name);
        if (ioctl(sockfd, SIOCGIFNETMASK, &netmask_req) == 0) {
            struct sockaddr_in* netmask = (struct sockaddr_in*)&netmask_req.ifr_netmask;
            printf("  Netmask: %s\n", inet_ntoa(netmask->sin_addr));
        } else {
            printf("  Netmask: N/A\n");
        }

        // Get Broadcast Address
        struct ifreq broad_req;
        strcpy(broad_req.ifr_name, item->ifr_name);
        if (ioctl(sockfd, SIOCGIFBRDADDR, &broad_req) == 0) {
            struct sockaddr_in* broadaddr = (struct sockaddr_in*)&broad_req.ifr_broadaddr;
            printf("  Broadcast Address: %s\n", inet_ntoa(broadaddr->sin_addr));
        } else {
            printf("  Broadcast Address: N/A\n");
        }

        // Get MAC Address
        struct ifreq mac_req;
        strcpy(mac_req.ifr_name, item->ifr_name);
        if (ioctl(sockfd, SIOCGIFHWADDR, &mac_req) == 0) {
            unsigned char *mac = (unsigned char *)mac_req.ifr_hwaddr.sa_data;
            printf("  MAC Address: %02x:%02x:%02x:%02x:%02x:%02x\n",
                   mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        } else {
            printf("  MAC Address: N/A\n");
        }

        printf("\n");
    }

    close(sockfd);
    return 0;
}*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

void print_interface_info(int sockfd, const char* ifname) {
    struct ifreq ifr;
    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, ifname, IFNAMSIZ);

    printf("Interface: %s\n", ifname);

    // Flags
    if (ioctl(sockfd, SIOCGIFFLAGS, &ifr) == 0) {
        printf("  Flags: ");
        if (ifr.ifr_flags & IFF_UP) printf("UP ");
        else printf("DOWN ");
        if (ifr.ifr_flags & IFF_BROADCAST) printf("BROADCAST ");
        if (ifr.ifr_flags & IFF_LOOPBACK) printf("LOOPBACK ");
        if (ifr.ifr_flags & IFF_RUNNING) printf("RUNNING ");
        if (ifr.ifr_flags & IFF_MULTICAST) printf("MULTICAST ");
        printf("\n");
    } else {
        perror("SIOCGIFFLAGS");
    }

    // IP Address
    if (ioctl(sockfd, SIOCGIFADDR, &ifr) == 0) {
        struct sockaddr_in* ipaddr = (struct sockaddr_in*)&ifr.ifr_addr;
        printf("  IP Address: %s\n", inet_ntoa(ipaddr->sin_addr));
    } else {
        printf("  IP Address: N/A\n");
    }

    // Netmask
    if (ioctl(sockfd, SIOCGIFNETMASK, &ifr) == 0) {
        struct sockaddr_in* netmask = (struct sockaddr_in*)&ifr.ifr_netmask;
        printf("  Netmask: %s\n", inet_ntoa(netmask->sin_addr));
    } else {
        printf("  Netmask: N/A\n");
    }

    // Broadcast Address
    if (ioctl(sockfd, SIOCGIFBRDADDR, &ifr) == 0) {
        struct sockaddr_in* broadaddr = (struct sockaddr_in*)&ifr.ifr_broadaddr;
        printf("  Broadcast Address: %s\n", inet_ntoa(broadaddr->sin_addr));
    } else {
        printf("  Broadcast Address: N/A\n");
    }

    // MAC Address
    if (ioctl(sockfd, SIOCGIFHWADDR, &ifr) == 0) {
        unsigned char *mac = (unsigned char *)ifr.ifr_hwaddr.sa_data;
        printf("  MAC Address: %02x:%02x:%02x:%02x:%02x:%02x\n",
               mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    } else {
        printf("  MAC Address: N/A\n");
    }

    printf("\n");
}

int main() {
    int sockfd;
    struct dirent *de;
    DIR *dr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(1);
    }

    dr = opendir("/sys/class/net/");
    if (dr == NULL) {
        perror("opendir");
        close(sockfd);
        exit(1);
    }

    printf("All network interfaces:\n\n");

    while ((de = readdir(dr)) != NULL) {
        if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
            continue;
        print_interface_info(sockfd, de->d_name);
    }

    closedir(dr);
    close(sockfd);
    return 0;
}


