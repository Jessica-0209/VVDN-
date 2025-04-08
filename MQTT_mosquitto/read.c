#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char broker_address[100];
int port;
char username[100];
char password[100];

void read_config() {
    FILE *fp = fopen("mqtt.txt", "r");
    if (!fp) {
        fprintf(stderr, "Failed to open config file!\n");
        exit(1);
    }

    char line[100];

    // Skip comment/empty lines
    while (fgets(line, sizeof(line), fp)) {
        if (line[0] == '#' || line[0] == '\n') 
	{
	    char temp[1000];
	    fgets(temp, sizeof(temp), fp);
	    continue;
        }
        line[strcspn(line, "\n")] = 0;  // Remove newline
        strcpy(broker_address, line);
        break;
    }

    // Read port
    char port_line[100];
    while (fgets(port_line, sizeof(port_line), fp)) {
        if (port_line[0] == '#') {
	    char temp[1000];
            fgets(temp, sizeof(temp), fp);
            continue;
        }
        port_line[strcspn(port_line, "\n")] = 0;
        port = atoi(port_line);
        break;
    }

    // Read username
    while (fgets(username, sizeof(username), fp)) {
        if (username[0] == '#') 
	{
	    char temp[1000];
            fgets(temp, sizeof(temp), fp);	 
            continue;
        }
        username[strcspn(username, "\n")] = 0;
        break;
    }

    // Read password
    while (fgets(password, sizeof(password), fp)) {
        if (password[0] == '#') 
	{
	    char temp[1000];
            fgets(temp, sizeof(temp), fp);
            continue;
        }
        password[strcspn(password, "\n")] = 0;
        break;
    }

    fclose(fp);
}

int main ()
{
	read_config();
	
	return 0;
}
