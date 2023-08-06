#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>

int main() {
    // create a TCP socket file descriptor for the server
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket error");
	return 1;
    }

    // set up server address info
    struct sockaddr_in address;
    address.sin_family = AF_INET;          // ipv4
    address.sin_port = htons(2000);        // server receives data on this port
    address.sin_addr.s_addr = INADDR_ANY;  // allow connections from any client

    // bind address to server socket
    int res = bind(sockfd,(struct sockaddr *)&address, sizeof(address));
    if (res == 0) printf("socket was bound successfully\r\n");

    return 0;
}

