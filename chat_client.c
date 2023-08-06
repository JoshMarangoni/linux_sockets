#include <stdio.h>       // for printf
#include <sys/socket.h>  // for socket
#include <netdb.h>       // for gethostbyname
#include <unistd.h>      // for close
#include <string.h>      // for string manipulation

#define SERVER_PORT 2000

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
    printf("client socket created successfully\r\n");

    // set up sockaddr struct with server info
    struct sockaddr_in address;
    address.sin_family = AF_INET;          // ipv4
    address.sin_port = htons(SERVER_PORT); // server port, big endian
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // localhost

    // attempt to establish a connection with the server
    // block until connection is established or an error occurs
    // if successful, open the client fd for reading and writing
    int result = connect(socketfd, (SA*)&address, sizeof(address));
    if (result < 0) {
        perror("connect error");
	close(socketfd);
	return 1;
    }


    close(socketfd);
    return 0;
}

