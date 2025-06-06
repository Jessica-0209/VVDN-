#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 1234
#define BUFFER_SIZE 1024

int main() 
{
    	int client_socket;
    	struct sockaddr_in server_addr;
    	char buffer[BUFFER_SIZE] = {0};
	char message[BUFFER_SIZE] = {0};

    	while(1)
	{
		// 1. Create the socket
    		client_socket = socket(AF_INET, SOCK_STREAM, 0);
    		if (client_socket < 0) 
    		{
        		perror("Socket creation failed");
        		exit(EXIT_FAILURE);
    		}
	
    		// 2. Set up the server address structure
    		memset(&server_addr, 0, sizeof(server_addr));
    		server_addr.sin_family = AF_INET;
    		server_addr.sin_port = htons(PORT);
    	
		if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) 
    		{
        		perror("Invalid address");
        		close(client_socket);
        		exit(EXIT_FAILURE);
    		}
	
    		// 3. Connect to the server
    		if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) 
    		{
        		perror("Connection failed");
        		close(client_socket);
        		exit(EXIT_FAILURE);
    		}

    		// 4. Send data to the server
    		printf("Enter message to send to server: ");
    		fgets(message, sizeof(message), stdin);
    		message[strcspn(message, "\n")] = '\0';
    	
		send(client_socket, message, strlen(message), 0);
	
    		// 5. Receive a message from the server
    		memset(buffer, 0, BUFFER_SIZE);
    		recv(client_socket, buffer, BUFFER_SIZE, 0);
    		printf("Received from server: %s\n", buffer);

    		// 6. Close the socket
    		close(client_socket);
	}

    	return 0;
}

