/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <sys/socket.h>

#define BUF_SIZE 8192

int main() 
{
    	int sock = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
    	if (sock < 0) 
    	{
        	perror("socket");
        	return 1;
    	}

    	struct sockaddr_nl sa = {0};
    	sa.nl_family = AF_NETLINK;

    	struct 
    	{
        	struct nlmsghdr nh;
        	struct ifinfomsg ifm;
    	} req = {0};

    	req.nh.nlmsg_len = NLMSG_LENGTH(sizeof(struct ifinfomsg));
    	req.nh.nlmsg_type = RTM_GETLINK;
    	req.nh.nlmsg_flags = NLM_F_REQUEST | NLM_F_DUMP;
    	req.ifm.ifi_family = AF_UNSPEC;

    	if (sendto(sock, &req, req.nh.nlmsg_len, 0, (struct sockaddr *)&sa, sizeof(sa)) < 0) 
    	{
        	perror("sendto");
        	return 1;
    	}

    	char buf[BUF_SIZE];
    	while (1) 
	{
    		ssize_t len = recv(sock, buf, BUF_SIZE, 0);
    		if (len < 0) 
    		{
        		perror("recv");
        		break;
    		}

    		struct nlmsghdr *nh;
    		for (nh = (struct nlmsghdr *)buf; NLMSG_OK(nh, len); nh = NLMSG_NEXT(nh, len)) 
    		{
        		if (nh->nlmsg_type == NLMSG_DONE)
			{
				return 0;
			}

        		if (nh->nlmsg_type == NLMSG_ERROR) 
			{
            			fprintf(stderr, "Netlink error\n");
            			return 1;
        		}

        		struct ifinfomsg *ifi = NLMSG_DATA(nh);
        		struct rtattr *rta = IFLA_RTA(ifi);
        		int rta_len = nh->nlmsg_len - NLMSG_LENGTH(sizeof(*ifi));

        		for (; RTA_OK(rta, rta_len); rta = RTA_NEXT(rta, rta_len)) 
			{
            			if (rta->rta_type == IFLA_IFNAME) 
	    			{
                			printf("Interface %d: %s\n", ifi->ifi_index, (char *)RTA_DATA(rta));
            			}
        		}
    		}
	}


    	close(sock);
    	return 0;
}*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <linux/if.h>
#include <linux/if_link.h>

void list_interfaces() {
    struct sockaddr_nl sa;
    struct nlmsghdr *nlh;
    struct ifinfomsg *ifi;
    int sock;

    sock = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
    if (sock < 0) {
        perror("Socket creation failed");
        return;
    }

    memset(&sa, 0, sizeof(sa));
    sa.nl_family = AF_NETLINK;

    // Create Netlink message to request interface list
    nlh = (struct nlmsghdr *) malloc(NLMSG_SPACE(sizeof(struct ifinfomsg)));
    memset(nlh, 0, NLMSG_SPACE(sizeof(struct ifinfomsg)));

    nlh->nlmsg_len = NLMSG_LENGTH(sizeof(struct ifinfomsg));
    nlh->nlmsg_type = RTM_GETLINK;
    nlh->nlmsg_flags = NLM_F_REQUEST;

    ifi = (struct ifinfomsg *) NLMSG_DATA(nlh);
    ifi->ifi_family = AF_UNSPEC;

    if (sendto(sock, nlh, nlh->nlmsg_len, 0, (struct sockaddr *) &sa, sizeof(sa)) < 0) {
        perror("Failed to send Netlink message");
    }

    // Receive response
    char buffer[4096];
    int len = recv(sock, buffer, sizeof(buffer), 0);
    if (len < 0) {
        perror("Failed to receive Netlink message");
    }

    struct nlmsghdr *hdr = (struct nlmsghdr *) buffer;
    while (NLMSG_OK(hdr, len)) {
        if (hdr->nlmsg_type == RTM_NEWLINK) {
            struct ifinfomsg *msg = NLMSG_DATA(hdr);
            struct rtattr *attr = (struct rtattr *) IFLA_RTA(msg);
            int remaining = NLMSG_PAYLOAD(hdr, sizeof(struct ifinfomsg));

            while (RTA_OK(attr, remaining)) {
                if (attr->rta_type == IFLA_IFNAME) {
                    printf("Interface: %s\n", (char *) RTA_DATA(attr));
                }
                attr = RTA_NEXT(attr, remaining);
            }
        }
        hdr = NLMSG_NEXT(hdr, len);
    }

    close(sock);
    free(nlh);
}

int main() {
    list_interfaces();
    return 0;
}

