#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <linux/if.h>
#include <linux/if_link.h>

#define NLMSG_TAIL(nmsg) \
    ((struct rtattr *) (((void *) (nmsg)) + NLMSG_ALIGN((nmsg)->nlmsg_len)))

void addattr_l(struct nlmsghdr *n, int maxlen, int type, void *data, int alen) 
{
    	int len = RTA_LENGTH(alen);
    	struct rtattr *rta = NLMSG_TAIL(n);
    	if (NLMSG_ALIGN(n->nlmsg_len) + RTA_ALIGN(len) > maxlen)
    	{
        	return;
	}
    	rta->rta_type = type;
    	rta->rta_len = len;
    	memcpy(RTA_DATA(rta), data, alen);
    	n->nlmsg_len = NLMSG_ALIGN(n->nlmsg_len) + RTA_ALIGN(len);
}

int bring_interface_up(const char *ifname) 
{
    	struct
    	{
        	struct nlmsghdr nh;
        	struct ifinfomsg ifi;
        	char buf[256];
    	} req;

    	int sock = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
    	if (sock < 0) 
    	{ 
		perror("socket"); 
		return 1; 
	}

    	memset(&req, 0, sizeof(req));
    	req.nh.nlmsg_len = NLMSG_LENGTH(sizeof(struct ifinfomsg));
    	req.nh.nlmsg_type = RTM_NEWLINK;
    	req.nh.nlmsg_flags = NLM_F_REQUEST | NLM_F_ACK;
    	req.ifi.ifi_family = AF_UNSPEC;
    	req.ifi.ifi_change = 0xFFFFFFFF;
    	req.ifi.ifi_flags = IFF_UP;

    	// get interface index
    	int ifindex = if_nametoindex(ifname);
    	if (!ifindex) 
    	{
        	perror("if_nametoindex");
        	return 1;
    	}
    	req.ifi.ifi_index = ifindex;

    	struct sockaddr_nl sa = { .nl_family = AF_NETLINK };

    	if (sendto(sock, &req, req.nh.nlmsg_len, 0, (struct sockaddr*)&sa, sizeof(sa)) < 0) 
    	{
        	perror("sendto");
        	return 1;
    	}

    	printf("%s brought up via Netlink!\n", ifname);
    	close(sock);
    	return 0;
}

int main() 
{
    	bring_interface_up("wlp44s0"); 
    	return 0;
}

