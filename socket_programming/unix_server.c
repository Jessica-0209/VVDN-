#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/home/vvsa/VVDN-/socket_programming/tmp/mysocket"

int main() 
{
    	int server_fd;
        int client_fd;
    	struct sockaddr_un addr;
    	char buffer[100] = {0};

    	// Create socket
    	server_fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    	if (server_fd == -1) 
    	{
        	perror("socket");
        	exit(EXIT_FAILURE);
	}
	
    	// Remove any existing socket file
    	unlink(SOCKET_PATH);

    	// Bind to socket path
    	memset(&addr, 0, sizeof(addr));
    	addr.sun_family = AF_UNIX;
    	strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

    	if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) 
	{
        	perror("bind");
    	    	exit(EXIT_FAILURE);
    	}

    	// Listen for connections
    	listen(server_fd, 5);

    	printf("Server waiting for connection...\n");
    	
	while(1)
	{
		client_fd = accept(server_fd, NULL, NULL);
    		if (client_fd == -1) 
    		{
        		perror("accept");
    	    		exit(EXIT_FAILURE);
    		}

    		// Read message from client
		memset(buffer, 0, sizeof(buffer));

    		read(client_fd, buffer, sizeof(buffer));
    		printf("Received from client: %s\n", buffer);
				
    		// Respond to client
    		write(client_fd, buffer, strlen(buffer) + 1);

    		// Clean up
    		close(client_fd);
	}
    	close(server_fd);
    	unlink(SOCKET_PATH); // Delete the socket file
    	
	return 0;
}

