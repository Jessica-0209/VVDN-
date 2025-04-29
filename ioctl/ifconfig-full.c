#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_INTERFACES 20

void print_interface_stats(const char *ifname) 
{
    	FILE *fp = fopen("/proc/net/dev", "r");
    	if (!fp) 
    	{
        	perror("fopen /proc/net/dev");
        	return;
    	}
	
    	char line[512];
    	// Skip first two lines
    	fgets(line, sizeof(line), fp);
    	fgets(line, sizeof(line), fp);

    	while (fgets(line, sizeof(line), fp)) 
    	{
        	char iface[64];
        	unsigned long rx_bytes, rx_packets, rx_errs, rx_drop, rx_fifo, rx_frame, rx_compressed, rx_multicast;
        	unsigned long tx_bytes, tx_packets, tx_errs, tx_drop, tx_fifo, tx_colls, tx_carrier, tx_compressed;

        	sscanf(line, "%[^:]: %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu", iface, &rx_bytes, &rx_packets, &rx_errs, &rx_drop, &rx_fifo, &rx_frame, &rx_compressed, &rx_multicast, &tx_bytes, &tx_packets, &tx_errs, &tx_drop, &tx_fifo, &tx_colls, &tx_carrier, &tx_compressed);

        	// Remove leading spaces
        	char *p = iface;
        	while (*p == ' ') p++;
	
        	if (strcmp(p, ifname) == 0) 
		{
           		printf("    RX packets: %lu  bytes: %lu\n", rx_packets, rx_bytes);
            		printf("    RX errors: %lu  dropped: %lu overruns: %lu frame: %lu\n", rx_errs, rx_drop, rx_fifo, rx_frame);
            		printf("    TX packets: %lu  bytes: %lu\n", tx_packets, tx_bytes);
            		printf("    TX errors: %lu  dropped: %lu overruns: %lu carrier: %lu collisions: %lu\n", tx_errs, tx_drop, tx_fifo, tx_carrier, tx_colls);
            		break;
        	}
    	}

    	fclose(fp);
}

int main() 
{
    	int sockfd;
    	struct ifconf ifc;
    	struct ifreq ifr[MAX_INTERFACES];
    	char buf[1024];
    	int interfaces, i;

    	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    	if (sockfd < 0) 
    	{
        	perror("socket");
        	exit(1);
    	}

    	ifc.ifc_len = sizeof(buf);
    	ifc.ifc_buf = buf;

    	if (ioctl(sockfd, SIOCGIFCONF, &ifc) == -1) 
    	{
        	perror("ioctl SIOCGIFCONF");
        	exit(1);
    	}

    	interfaces = ifc.ifc_len / sizeof(struct ifreq);
    	memcpy(ifr, ifc.ifc_req, ifc.ifc_len);

	printf("All network interfaces:\n\n");

	for (i = 0; i < interfaces; i++) 
	{
    		struct ifreq *item = &ifr[i];

    		printf("Interface: %s\n", item->ifr_name);

    		// Get flags
    		if (ioctl(sockfd, SIOCGIFFLAGS, item) == 0) 
    		{
        		printf("  Flags: ");
        		if (item->ifr_flags & IFF_UP) printf("UP ");
        		if (item->ifr_flags & IFF_BROADCAST) printf("BROADCAST ");
        		if (item->ifr_flags & IFF_RUNNING) printf("RUNNING ");
        		if (item->ifr_flags & IFF_LOOPBACK) printf("LOOPBACK ");
        		if (item->ifr_flags & IFF_MULTICAST) printf("MULTICAST ");
        		printf("\n");
    		}

    		// IP Address (optional)
    		if (ioctl(sockfd, SIOCGIFADDR, item) == 0) 
    		{
        		struct sockaddr_in *ipaddr = (struct sockaddr_in *)&item->ifr_addr;
        		printf("  IP Address: %s\n", inet_ntoa(ipaddr->sin_addr));
    		}

    		// Netmask (optional)
    		if (ioctl(sockfd, SIOCGIFNETMASK, item) == 0) 
    		{
        		struct sockaddr_in *netmask = (struct sockaddr_in *)&item->ifr_netmask;
        		printf("  Netmask: %s\n", inet_ntoa(netmask->sin_addr));
    		}
	
    		// Broadcast (optional)
    		if (ioctl(sockfd, SIOCGIFBRDADDR, item) == 0) 
    		{
        		struct sockaddr_in *broadaddr = (struct sockaddr_in *)&item->ifr_broadaddr;
        		printf("  Broadcast Address: %s\n", inet_ntoa(broadaddr->sin_addr));
    		}

    		// MAC
    		if (ioctl(sockfd, SIOCGIFHWADDR, item) == 0) 
    		{
        		unsigned char *mac = (unsigned char *)item->ifr_hwaddr.sa_data;
        		printf("  MAC Address: %02x:%02x:%02x:%02x:%02x:%02x\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    		}

    		// MTU
    		if (ioctl(sockfd, SIOCGIFMTU, item) == 0) 
    		{
        		printf("  MTU: %d\n", item->ifr_mtu);
    		}

    		// TX queue length
    		if (ioctl(sockfd, SIOCGIFTXQLEN, item) == 0) 
    		{
        		printf("  TX Queue Length: %d\n", item->ifr_qlen);
    		}

    		// RX/TX stats from /proc/net/dev
    		print_interface_stats(item->ifr_name);
    		printf("\n");
	}

	
    	close(sockfd);
    	return 0;
}

