#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() 
{
    	int server_socket; 
	int client_socket;
	int opt = 1;
    	struct sockaddr_in server_addr, client_addr;
    	char buffer[BUFFER_SIZE];
    	socklen_t client_len = sizeof(client_addr);

    	// 1. Create the socket
    	server_socket = socket(AF_INET, SOCK_STREAM, 0);
    	if (server_socket < 0) 
    	{
        	perror("Socket creation failed");
        	exit(EXIT_FAILURE);
    	}

    	// 2. Set up the server address structure
    	memset(&server_addr, 0, sizeof(server_addr));  //clears the server_addr memory before filling 
    	server_addr.sin_family = AF_INET;
    	server_addr.sin_addr.s_addr = INADDR_ANY;  //accepts connections from any IP address
    	server_addr.sin_port = htons(PORT);//convert to network byte order(big endian) coz both ends should use same format(little/big endian)

	setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)); //to reuse the same socket

    	// 3. Bind the socket to the IP and port
    	if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) 
	{
        	perror("Binding failed");
        	close(server_socket);
        	exit(EXIT_FAILURE);
    	}

    	// 4. Listen for incoming connections
    	if (listen(server_socket, 5) < 0) 
	{
        	perror("Listen failed");
        	close(server_socket);
        	exit(EXIT_FAILURE);
    	}
	
    	printf("Server is listening on port %d...\n", PORT);

	while(1)
	{
    		// 5. Accept a connection from a client
    		client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);
    		if (client_socket < 0) 
    		{
        		perror("Server accept failed");
        		close(server_socket);
        		exit(EXIT_FAILURE);
		}
	
    		printf("Client connected\n");

    		// 6. Receive and send data
    		memset(buffer, 0, BUFFER_SIZE);
    		recv(client_socket, buffer, BUFFER_SIZE, 0);
    		printf("Received from client: %s\n", buffer);

    		// Send a message to the client
    		send(client_socket, buffer, strlen(buffer), 0);

    		// 7. Close the sockets
    		close(client_socket);
	}	
    	close(server_socket);

    	return 0;
}

