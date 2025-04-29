#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <sys/socket.h>

void bring_interface_down(const char *ifname) {
    struct sockaddr_nl sa;
    struct nlmsghdr *nlh;
    struct ifinfomsg *ifinfo;
    int sock;

    // Create Netlink socket
    sock = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
    if (sock < 0) {
        perror("Socket creation failed");
        return;
    }

    // Set up address structure
    memset(&sa, 0, sizeof(sa));
    sa.nl_family = AF_NETLINK;

    // Allocate memory for Netlink message
    nlh = (struct nlmsghdr *) malloc(NLMSG_SPACE(sizeof(struct ifinfomsg)));
    memset(nlh, 0, NLMSG_SPACE(sizeof(struct ifinfomsg)));

    nlh->nlmsg_len = NLMSG_LENGTH(sizeof(struct ifinfomsg));
    nlh->nlmsg_type = RTM_SETLINK;  // Request to change the link state
    nlh->nlmsg_flags = NLM_F_REQUEST;

    // Set up interface information (down the interface)
    ifinfo = (struct ifinfomsg *) NLMSG_DATA(nlh);
    ifinfo->ifi_family = AF_UNSPEC;  // Default
    ifinfo->ifi_change = 0xFFFFFFFF; // Change all flags

    // Find the interface index using if_nametoindex
    int ifindex = if_nametoindex(ifname);
    if (ifindex == 0) {
        perror("if_nametoindex failed");
        close(sock);
        free(nlh);
        return;
    }

    ifinfo->ifi_index = ifindex;

    // Send the Netlink message to bring the interface down
    if (sendto(sock, nlh, nlh->nlmsg_len, 0, (struct sockaddr *) &sa, sizeof(sa)) < 0) {
        perror("Failed to send Netlink message");
        close(sock);
        free(nlh);
        return;
    }

    printf("%s brought down via Netlink!\n", ifname);

    // Clean up
    close(sock);
    free(nlh);
}

int main() {
    bring_interface_down("wlp44s0");  // Replace with your interface name
    return 0;
}

