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
#include <mosquitto.h>
#include <cjson/cJSON.h>
#include <time.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/wireless.h> 

#define MAX_IFACES 10
#define MAX_IFNAME 16

#define MAX_RESULTS 100
cJSON *networks_array = NULL;

#ifndef NL80211_BSS_CHAN_FREQ
#define NL80211_BSS_CHAN_FREQ 9  // Channel frequency attribute ID
#endif

static int nl80211_id;

void print_current_connection(const char *ifname)
{
    	int sockfd;
    	struct iwreq req;
    	char ssid[33] = {0};
    	unsigned char bssid[6];
    	double freq;
    	int freq_mhz = 0;
    	int channel = 0;

    	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    	if (sockfd < 0) 
	{
        	perror("socket");
        	return;
    	}

    	memset(&req, 0, sizeof(struct iwreq));
    	strncpy(req.ifr_name, ifname, IFNAMSIZ - 1);

    	// Get SSID
    	req.u.essid.pointer = ssid;
    	req.u.essid.length = sizeof(ssid);
    	req.u.essid.flags = 0;
    	if (ioctl(sockfd, SIOCGIWESSID, &req) == -1) 
	{
        	perror("SIOCGIWESSID");
    	}

    	// Get BSSID (AP MAC)
    	if (ioctl(sockfd, SIOCGIWAP, &req) == -1) 
	{
        	perror("SIOCGIWAP");
    	} 
	else 
	{
        	memcpy(bssid, req.u.ap_addr.sa_data, 6);
    	}

    	// Get frequency
    	if (ioctl(sockfd, SIOCGIWFREQ, &req) == -1) 
	{
        	perror("SIOCGIWFREQ");
    	} 
	else 
	{
        	freq = req.u.freq.m;  // frequency in Hz
        	while (freq > 1000000000)
		{
            		freq /= 1000000;  // convert to MHz
		}
        	freq_mhz = (int)freq;
        	channel = freq_to_channel(freq_mhz);
    	}

    	printf("\n📡 Current Connection Details:\n");
    	printf("  Interface       : %s\n", ifname);
    	printf("  Connection      : %s\n", ssid[0] ? "Connected" : "Not Connected");
    	printf("  SSID            : %s\n", ssid[0] ? ssid : "<unknown>");
    	printf("  BSSID           : %02x:%02x:%02x:%02x:%02x:%02x\n", bssid[0], bssid[1], bssid[2], bssid[3], bssid[4], bssid[5]);
    	printf("  Frequency       : %d MHz\n", freq_mhz);
    	printf("  Channel         : %d\n\n", channel);

    	close(sockfd);
}

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

static int count = 0;

static int callback_handler(struct nl_msg *msg, void *arg) 
{
	
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
        	signal = nla_get_s32(bss[NL80211_BSS_SIGNAL_MBM]);
    	}

    	if (bss[NL80211_BSS_CHAN_FREQ]) 
	{
        	freq = nla_get_u32(bss[NL80211_BSS_CHAN_FREQ]);
        	channel = freq_to_channel(freq);
 	}

	if (!networks_array)
	{
    		networks_array = cJSON_CreateArray();  
	}

	cJSON *net = cJSON_CreateObject();
	cJSON_AddStringToObject(net, "ssid", ssid[0] ? ssid : "<hidden>");
	cJSON_AddStringToObject(net, "bssid", mac_addr);
	cJSON_AddNumberToObject(net, "signal_strength", signal / 100.0);
	cJSON_AddNumberToObject(net, "channel", channel);
	cJSON_AddNumberToObject(net, "frequency", freq);

	cJSON_AddItemToArray(networks_array, net);
	
	count++;
    	return NL_OK;
}

int get_first_wireless_interface(char *ifname)
{
    	struct ifreq ifr[MAX_IFACES];
    	struct ifconf ifc;
    	int sock, i;

    	sock = socket(AF_INET, SOCK_DGRAM, 0);
    	if (sock < 0) 
    	{
        	perror("socket");
        	return -1;
    	}

    	ifc.ifc_len = sizeof(ifr);
    	ifc.ifc_req = ifr;

    	if (ioctl(sock, SIOCGIFCONF, &ifc) < 0) 
    	{
        	perror("ioctl SIOCGIFCONF");
        	close(sock);
        	return -1;
    	}

    	int n = ifc.ifc_len / sizeof(struct ifreq);

    	for (i = 0; i < n; i++) 
    	{
        	struct ifreq wreq;
        	strncpy(wreq.ifr_name, ifr[i].ifr_name, IFNAMSIZ);

              	if (ioctl(sock, SIOCGIWNAME, &wreq) >= 0) 
		{
            		strncpy(ifname, wreq.ifr_name, MAX_IFNAME - 1);
            		ifname[MAX_IFNAME - 1] = '\0';
            		close(sock);
            		return 0;
        	}
    	}

    	close(sock);
    	return -1; 
}

static int ack_received = 0;

void on_ack_message(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message)
{
    	if (message->payloadlen)
    	{
        	printf("%s\n", (char *)message->payload);
        	ack_received = 1;
    	}
}

void scan_report_mqtt(const char *payload)
{
    	mosquitto_lib_init();

    	struct mosquitto *mosq = mosquitto_new("scan_report", true, NULL);
    	if (!mosq)
    	{
        	fprintf(stderr, "Failed to create mosquitto client\n");
        	return;
    	}

    	mosquitto_username_pw_set(mosq, "newuser", "mqtt");
    	mosquitto_message_callback_set(mosq, on_ack_message);

    	if (mosquitto_connect(mosq, "localhost", 1883, 60) == MOSQ_ERR_SUCCESS)
    	{
        	ack_received = 0;  
	
        	mosquitto_publish(mosq, NULL, "scan/report/wifi", strlen(payload), payload, 0, false);
        	printf("MQTT scan report published.\n");
	
        	mosquitto_subscribe(mosq, NULL, "scan/ack", 0);

        	int loops = 0;
        	while (!ack_received && loops < 20)  
        	{	
            		mosquitto_loop(mosq, 100, 1);
            		loops++;
        	}

        	if (!ack_received)
        	{
            		printf("No acknowledgment received within timeout.\n");
        	}
    	}
    	else
    	{
        	fprintf(stderr, "MQTT connection failed: %s\n", mosquitto_strerror(mosquitto_connect(mosq, "localhost", 1883, 60)));
    	}

    	mosquitto_disconnect(mosq);
    	mosquitto_destroy(mosq);
    	mosquitto_lib_cleanup();
}


void get_current_time_str(char *buffer, size_t size) {
    	time_t rawtime;
    	struct tm *timeinfo;

    	time(&rawtime);
    	timeinfo = localtime(&rawtime);
    	strftime(buffer, size, "%Y-%m-%d %H:%M:%S", timeinfo);  // Format: YYYY-MM-DD HH:MM:SS
}

int get_ifindex_ioctl(const char *ifname)
{
    	int sock = socket(AF_INET, SOCK_DGRAM, 0);
    	if (sock < 0) 
    	{
        	perror("socket");
        	return -1;
    	}

    	struct ifreq ifr;
    	memset(&ifr, 0, sizeof(ifr));
    	strncpy(ifr.ifr_name, ifname, IFNAMSIZ-1);

    	if (ioctl(sock, SIOCGIFINDEX, &ifr) < 0) 
	{
        	perror("ioctl SIOCGIFINDEX");
        	close(sock);
        	return -1;
    	}

    	close(sock);
    	return ifr.ifr_ifindex;
}

int main()
{
    	extern int count;
    	char ifname[MAX_IFNAME];
	
    	if (get_first_wireless_interface(ifname) < 0) 
    	{
        	fprintf(stderr, "No wireless interface found.\n");
        	return -1;
    	}

	print_current_connection(ifname);

    	printf("Using wireless interface: %s\n", ifname);
	
    	while (1)
    	{
        	count = 0;

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

        	int ifindex = get_ifindex_ioctl(ifname);
        	if (ifindex < 0) 
        	{
            		fprintf(stderr, "Failed to get interface index via ioctl\n");
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

        	if (networks_array && cJSON_GetArraySize(networks_array) > 0) 
        	{
            		char time_str[20];
            		get_current_time_str(time_str, sizeof(time_str));

            		cJSON *report = cJSON_CreateObject();
            		cJSON_AddStringToObject(report, "interface", ifname);
            		cJSON_AddStringToObject(report, "timestamp", time_str);
            		cJSON_AddItemToObject(report, "networks", networks_array);
            		networks_array = NULL;    
            
			char *payload = cJSON_Print(report);
			
            		if (payload) 
            		{
                		scan_report_mqtt(payload);
                		free(payload);
            		}    
            		else     
            		{
                		fprintf(stderr, "Failed to generate JSON payload.\n");
            		}

            		cJSON_Delete(report);
        	}     
        	else 
        	{
            		printf("No networks found to report.\n");
            		if (networks_array)
            		{
                		cJSON_Delete(networks_array);
                		networks_array = NULL;
            		}
        	}

        	nl_socket_free(sock);
        	sleep(10);
    	}
    	return 0;
}
