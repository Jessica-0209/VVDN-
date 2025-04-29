// netlink_listen.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <sys/socket.h>

#define BUFLEN 8192

int main() {
    struct sockaddr_nl sa;
    int sock = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
    if (sock < 0) {
        perror("socket");
        return 1;
    }

    memset(&sa, 0, sizeof(sa));
    sa.nl_family = AF_NETLINK;
    sa.nl_groups = RTMGRP_LINK; // subscribe to interface events

    if (bind(sock, (struct sockaddr*)&sa, sizeof(sa)) < 0) {
        perror("bind");
        close(sock);
        return 1;
    }

    char buf[BUFLEN];
    printf("Listening for Netlink interface events...\n");

    while (1) {
        ssize_t len = recv(sock, buf, sizeof(buf), 0);
        if (len < 0) {
            perror("recv");
            break;
        }

        struct nlmsghdr *nh = (struct nlmsghdr *)buf;
        for (; NLMSG_OK(nh, len); nh = NLMSG_NEXT(nh, len)) {
            if (nh->nlmsg_type == RTM_NEWLINK || nh->nlmsg_type == RTM_DELLINK) {
                printf("Interface state changed (RTM_NEWLINK or RTM_DELLINK received)\n");
            }
        }
    }

    close(sock);
    return 0;
}

