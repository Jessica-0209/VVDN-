#include <netlink/netlink.h>
#include <netlink/genl/genl.h>
#include <netlink/genl/ctrl.h>
#include <netlink/msg.h>
#include <netlink/attr.h>
#include <net/if.h>
#include <linux/nl80211.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>

#ifndef NL80211_BSS_CHAN_FREQ
#define NL80211_BSS_CHAN_FREQ 9  // Channel frequency attribute ID
#endif

#define MAX_IFNAME 100

static int nl80211_id;

int freq_to_channel(int freq) 
{
    	if (freq >= 2412 && freq <= 2472)
	{
		printf("2.4 GHz freq: %d => channel %d\n", freq, (freq - 2407) / 5);
        	return (freq - 2407) / 5;
	}
    	else if (freq == 2484)
	{
        	return 14;
	}
    	else if (freq >= 5180 && freq <= 5825)
	{
		printf("5 GHz freq: %d => channel %d\n", freq, (freq - 5000) / 5);
        	return (freq - 5000) / 5;
	}
    	else
	{
		printf("Invalid freq: %d => channel 0\n", freq);
        	return 0;
	}
}

static int callback_handler(struct nl_msg *msg, void *arg) 
{
	static int count = 0;
	
	if(count >= 10)
	{
		return NL_SKIP;
	}

    	struct nlattr *attrs[NL80211_ATTR_MAX + 1];
    	struct genlmsghdr *gnlh = nlmsg_data(nlmsg_hdr(msg));
    	struct nlattr *bss[NL80211_BSS_MAX + 1];
    	char mac_addr[20] = {0};
    	char ssid[33] = {0};
	int freq = 2412;
    	int channel = 0;
    	int32_t signal = 0;

    	nla_parse(attrs, NL80211_ATTR_MAX, genlmsg_attrdata(gnlh, 0), genlmsg_attrlen(gnlh, 0), NULL);

    	if (!attrs[NL80211_ATTR_BSS])
	{
        	return NL_SKIP;
	}

    	nla_parse_nested(bss, NL80211_BSS_MAX, attrs[NL80211_ATTR_BSS], NULL);

    	if (bss[NL80211_BSS_BSSID]) 
	{
        	unsigned char *mac = nla_data(bss[NL80211_BSS_BSSID]);
        	snprintf(mac_addr, sizeof(mac_addr), "%02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    	}

    	if (bss[NL80211_BSS_INFORMATION_ELEMENTS]) 
	{
        	unsigned char *ie = nla_data(bss[NL80211_BSS_INFORMATION_ELEMENTS]);
        	int ielen = nla_len(bss[NL80211_BSS_INFORMATION_ELEMENTS]);
        	int i = 0;

        	while (i + 1 < ielen) 
		{
            		int id = ie[i];
            		int len = ie[i + 1];
	
            		if (i + 2 + len > ielen)
			{
                		break;
			}

            		if (id == 0 && len <= 32) 
			{
                		memcpy(ssid, &ie[i + 2], len);
                		ssid[len] = '\0';
                		break;
            		}
            		i += len + 2;
        	}
    	}

    	if (bss[NL80211_BSS_SIGNAL_MBM]) 
	{
        	signal = (int32_t)nla_get_u32(bss[NL80211_BSS_SIGNAL_MBM]);
    	}

    	if (bss[NL80211_BSS_CHAN_FREQ]) 
	{
        	freq = nla_get_u32(bss[NL80211_BSS_CHAN_FREQ]);
        	channel = freq_to_channel(freq);
 	}

    	printf("SSID: %-20s  BSSID: %-17s  Signal: %4.1f dBm  Channel: %2d (Freq: %d MHz)\n", ssid[0] ? ssid : "<hidden>", mac_addr, signal / 100.0, channel, freq);

	count++;
    	return NL_OK;
}

int main(int argc, char *argv[]) 
{
	if (argc < 2) 
	{
        	fprintf(stderr, "Usage: %s <interface-name>\n", argv[0]);
        	return -1;
    	}

    	char ifname[MAX_IFNAME];
    	strncpy(ifname, argv[1], MAX_IFNAME - 1);
    	ifname[MAX_IFNAME - 1] = '\0';

    	struct nl_sock *sock = nl_socket_alloc();
    	if (!sock) 
	{
        	fprintf(stderr, "Failed to allocate netlink socket.\n");
        	return -1;
    	}

    	if (genl_connect(sock)) 
	{
        	fprintf(stderr, "Failed to connect to generic netlink.\n");
        	nl_socket_free(sock);
        	return -1;
    	}

    	nl80211_id = genl_ctrl_resolve(sock, "nl80211");
    	if (nl80211_id < 0) 
	{
        	fprintf(stderr, "nl80211 not found.\n");
        	nl_socket_free(sock);
        	return -1;
    	}
  
    	int ifindex = if_nametoindex(ifname);
    	if (!ifindex) 
	{
        	perror("if_nametoindex");
        	nl_socket_free(sock);
        	return -1;
    	}

    	struct nl_msg *msg = nlmsg_alloc();
    	if (!msg) 
	{
        	fprintf(stderr, "Failed to allocate netlink message.\n");
        	nl_socket_free(sock);
        	return -1;
    	}

    	genlmsg_put(msg, 0, 0, nl80211_id, 0, NLM_F_DUMP, NL80211_CMD_GET_SCAN, 0);
    	nla_put_u32(msg, NL80211_ATTR_IFINDEX, ifindex);

    	nl_socket_modify_cb(sock, NL_CB_VALID, NL_CB_CUSTOM, callback_handler, NULL);

    	if (nl_send_auto(sock, msg) < 0) 
	{
        	fprintf(stderr, "Failed to send message.\n");
        	nlmsg_free(msg);
        	nl_socket_free(sock);
        	return -1;
    	}

    	nlmsg_free(msg);
    	nl_recvmsgs_default(sock);
    	nl_socket_free(sock);

    	return 0;
}

