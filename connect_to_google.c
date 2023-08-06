#include <stdio.h>       // for printf
#include <sys/socket.h>  // for socket
#include <netdb.h>       // for gethostbyname
#include <unistd.h>      // for close
#include <string.h>      // for string manipulation

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

    // set up hostname
    const char* hostname = "google.com";
    int port = 80;
    struct hostent *host = gethostbyname(hostname);
    if (host == NULL) {
        perror("gethostbyname");
	return 1;
    }

    // set up sockaddr struct with server info
    struct sockaddr_in address;
    address.sin_family = AF_INET;   // ipv4
    address.sin_port = htons(port); // server port, big endian
    address.sin_addr.s_addr = *(in_addr_t*)host->h_addr; // server ip

    // attempt to establish a connection with the server
    // block until connection is established or an error occurs
    // if successful, open the client fd for reading and writing
    int result = connect(socketfd, (SA*)&address, sizeof(address));
    if (result < 0) {
        perror("connect error");
	close(socketfd);
	return 1;
    }
    printf("conneted to %s:%d\n\r", hostname, port);

    // send an HTTP GET request to server
    char* msg;
    msg ="GET / HTTP/1.1\r\nHost: www.google.com\r\n\r\n";
    send(socketfd, msg, strlen(msg), 0);

    // receive response from server
    char buffer[1024];
    recv(socketfd, buffer, 1024, 0);

    printf("Response was: %s\r\n", buffer);

    close(socketfd);

    return 0;
}

