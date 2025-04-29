#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <net/if.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <arpa/inet.h>

#define NLMSG_TAIL(nmsg) \
    ((struct rtattr *) (((void *) (nmsg)) + NLMSG_ALIGN((nmsg)->nlmsg_len)))

void addattr_l(struct nlmsghdr *n, size_t maxlen, int type, const void *data, size_t datalen) {
    size_t len = RTA_LENGTH(datalen);
    struct rtattr *rta;

    if (NLMSG_ALIGN(n->nlmsg_len) + RTA_ALIGN(len) > maxlen) {
        fprintf(stderr, "addattr_l: message exceeded bound\n");
        exit(1);
    }

    rta = NLMSG_TAIL(n);
    rta->rta_type = type;
    rta->rta_len = len;
    memcpy(RTA_DATA(rta), data, datalen);
    n->nlmsg_len = NLMSG_ALIGN(n->nlmsg_len) + RTA_ALIGN(len);
}

int main() {
    int sock;
    struct {
        struct nlmsghdr n;
        struct rtmsg r;
        char buf[4096];
    } req;
    struct sockaddr_nl sa;
    struct in_addr dst_addr, gw_addr;
    int if_index;

    // Get output interface index (wlp44s0)
    if_index = if_nametoindex("wlp44s0");
    if (if_index == 0) {
        perror("if_nametoindex");
        return 1;
    }

    // Create socket
    sock = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
    if (sock < 0) {
        perror("socket");
        return 1;
    }

    memset(&sa, 0, sizeof(sa));
    sa.nl_family = AF_NETLINK;

    memset(&req, 0, sizeof(req));
    req.n.nlmsg_len = NLMSG_LENGTH(sizeof(struct rtmsg));
    req.n.nlmsg_type = RTM_NEWROUTE;
    req.n.nlmsg_flags = NLM_F_REQUEST | NLM_F_CREATE | NLM_F_EXCL;
    req.n.nlmsg_seq = 1;

    req.r.rtm_family = AF_INET;
    req.r.rtm_table = RT_TABLE_MAIN;
    req.r.rtm_protocol = RTPROT_BOOT;
    req.r.rtm_scope = RT_SCOPE_UNIVERSE;
    req.r.rtm_type = RTN_UNICAST;
    req.r.rtm_dst_len = 24; // Subnet mask 255.255.255.0

    // Set destination network
    if (!inet_aton("10.1.1.0", &dst_addr)) {
        fprintf(stderr, "Invalid destination address\n");
        return 1;
    }
    addattr_l(&req.n, sizeof(req), RTA_DST, &dst_addr, sizeof(dst_addr));

    // Set output interface
    addattr_l(&req.n, sizeof(req), RTA_OIF, &if_index, sizeof(if_index));

    // Set gateway
    if (!inet_aton("172.24.12.1", &gw_addr)) {
        fprintf(stderr, "Invalid gateway address\n");
        return 1;
    }
    addattr_l(&req.n, sizeof(req), RTA_GATEWAY, &gw_addr, sizeof(gw_addr));

    // Send message
    if (sendto(sock, &req, req.n.nlmsg_len, 0, (struct sockaddr *)&sa, sizeof(sa)) < 0) {
        perror("sendto");
        close(sock);
        return 1;
    }

    printf("Route added successfully: 10.1.1.0/24 via 172.24.12.1 dev wlp44s0\n");

    close(sock);
    return 0;
}

