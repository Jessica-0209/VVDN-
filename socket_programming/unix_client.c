#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/home/vvsa/VVDN-/socket_programming/tmp/mysocket"

int main() 
{
    	int client_fd;
    	struct sockaddr_un addr;
    	char buffer[100] = {0};
	char message[100] = {0};
	
	while(1)
	{
    		// Create socket
    		client_fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    		if (client_fd == -1) 
    		{
        		perror("socket");
        		exit(EXIT_FAILURE);
    		}

    		// Setup address
    		memset(&addr, 0, sizeof(addr));
    		addr.sun_family = AF_UNIX;
    		strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);
	
    		// Connect to server
    		if (connect(client_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) 
    		{
        		perror("connect");
        		exit(EXIT_FAILURE);
    		}
		
    		// Send message to server
		printf("Enter message to send: ");
        	fgets(message, sizeof(message), stdin);

    		message[strcspn(message, "\n")] = '\0';
		
		write(client_fd, message, strlen(message) + 1);

		memset(buffer, 0, sizeof(buffer));

    		// Read response
    		read(client_fd, buffer, sizeof(buffer));
    		printf("Received from server: %s\n", buffer);
	
    		close(client_fd);
	}
	
	return 0;
}

