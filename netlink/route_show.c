#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>

#define BUFFER_SIZE 8192

// Utility to parse and print the route attributes
void parse_route(struct nlmsghdr *nlh) {
    struct rtmsg *route_entry = (struct rtmsg *)NLMSG_DATA(nlh);
    int len = RTM_PAYLOAD(nlh);
    struct rtattr *attr = (struct rtattr *)RTM_RTA(route_entry);

    char dst[INET6_ADDRSTRLEN] = "";
    char gw[INET6_ADDRSTRLEN] = "";
    char ifname[IF_NAMESIZE] = "";
    uint32_t oif = 0;

    for (; RTA_OK(attr, len); attr = RTA_NEXT(attr, len)) {
        switch (attr->rta_type) {
            case RTA_DST:
                if (route_entry->rtm_family == AF_INET) {
                    inet_ntop(AF_INET, RTA_DATA(attr), dst, sizeof(dst));
                } else if (route_entry->rtm_family == AF_INET6) {
                    inet_ntop(AF_INET6, RTA_DATA(attr), dst, sizeof(dst));
                }
                break;
            case RTA_GATEWAY:
                if (route_entry->rtm_family == AF_INET) {
                    inet_ntop(AF_INET, RTA_DATA(attr), gw, sizeof(gw));
                } else if (route_entry->rtm_family == AF_INET6) {
                    inet_ntop(AF_INET6, RTA_DATA(attr), gw, sizeof(gw));
                }
                break;
            case RTA_OIF:
                oif = *(uint32_t *)RTA_DATA(attr);
                if_indextoname(oif, ifname);
                break;
        }
    }

    printf("Destination: %-20s Gateway: %-20s Interface: %s\n",
           *dst ? dst : "default",
           *gw ? gw : "*",
           *ifname ? ifname : "unknown");
}

int main() {
    int sock = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
    if (sock < 0) {
        perror("socket");
        return 1;
    }

    struct sockaddr_nl sa = {
        .nl_family = AF_NETLINK
    };

    if (bind(sock, (struct sockaddr *)&sa, sizeof(sa)) < 0) {
        perror("bind");
        close(sock);
        return 1;
    }

    // Request message to get routes
    char buffer[BUFFER_SIZE];
    struct nlmsghdr *nlh = (struct nlmsghdr *)buffer;
    struct rtmsg *rtm = (struct rtmsg *)(buffer + sizeof(struct nlmsghdr));

    memset(buffer, 0, sizeof(buffer));
    nlh->nlmsg_len = NLMSG_LENGTH(sizeof(struct rtmsg));
    nlh->nlmsg_type = RTM_GETROUTE;
    nlh->nlmsg_flags = NLM_F_REQUEST | NLM_F_DUMP;
    nlh->nlmsg_seq = 1;
    nlh->nlmsg_pid = getpid();

    rtm->rtm_family = AF_INET;  // Change to AF_INET6 for IPv6
    rtm->rtm_table = RT_TABLE_MAIN;

    struct iovec iov = { .iov_base = buffer, .iov_len = nlh->nlmsg_len };
    struct msghdr msg = {
        .msg_name = &sa,
        .msg_namelen = sizeof(sa),
        .msg_iov = &iov,
        .msg_iovlen = 1
    };

    if (sendmsg(sock, &msg, 0) < 0) {
        perror("sendmsg");
        close(sock);
        return 1;
    }

    // Read response
    while (1) {
        ssize_t len = recv(sock, buffer, sizeof(buffer), 0);
        if (len < 0) {
            perror("recv");
            break;
        }

        for (nlh = (struct nlmsghdr *)buffer; NLMSG_OK(nlh, len); nlh = NLMSG_NEXT(nlh, len)) {
            if (nlh->nlmsg_type == NLMSG_DONE)
                break;
            if (nlh->nlmsg_type == NLMSG_ERROR) {
                fprintf(stderr, "Netlink error\n");
                break;
            }

            parse_route(nlh);
        }
    }

    close(sock);
    return 0;
}
