#include <stdio.h>       // for printf
#include <sys/socket.h>  // for socket
#include <netdb.h>       // for gethostbyname
#include <unistd.h>      // for close
#include <string.h>      // for string manipulation

#define SERVER_PORT 2002

// connect, bind, and accept except pointers to
// a generic socket address (protocol independent).
// use this type for casting
typedef struct sockaddr SA;

int main() {
    // create an IPv4, TCP socket file descriptor
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0) {
        perror("socket error");
	return 1;
    }
    printf("server socket created successfully\r\n");

    // set up sockaddr struct for the server
    struct sockaddr_in address;
    address.sin_family = AF_INET; // ipv4
    address.sin_port = htons(SERVER_PORT); // server port, big endian
    address.sin_addr.s_addr = INADDR_ANY;  // allow connections from any client

    // bind the server sockfd with the server sockaddr struct
    int result = bind(socketfd, (SA*)&address, sizeof(address));
    if (result < 0) {
        perror("bind error");
	close(socketfd);
	return 1;
    }
    printf("bind successful\r\n");

    // tell OS to convert socketfd to a server socket
    // set the connection request backlog queue size to a large number
    result = listen(socketfd, 1024);
    if (result < 0){
        perror("listen error");
        close(socketfd);
	return 1;
    }

    // wait for connection requests from clients
    struct sockaddr_in client_address;
    int client_addr_size = sizeof(client_address);
    int connfd = accept(socketfd, (SA*)&client_address, &client_addr_size);

    char buffer[1024];
    recv(connfd, buffer, 1024, 0);

    printf("%s\n\r", buffer);
    close(connfd);
    close(socketfd);
    return 0;
}

