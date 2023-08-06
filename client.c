#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>

int main() {
    // create a TCP socket file descriptor on localhost
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0) {
        perror("socket error");
	return 1;
    }

    // set up hostname
    const char* hostname = "google.com";
    int port = 80;
    struct hostent *host = gethostbyname(hostname);
    if (host == NULL) {
        perror("gethostbyname");
	return 1;
    }

    // set up server info
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = *(in_addr_t*)host->h_addr;

    int result = connect(socketfd, (struct sockaddr*)&address, sizeof address);
    if (result < 0) {
        perror("connect error");
	close(socketfd);
	return 1;
    }

    printf("conneted to %s:%d\n\r", hostname, port);

    // send an HTTP GET request to server
    char* msg;
    msg ="GET \\ HTTP/1.1\r\nHost:google.com\r\n\r\n";
    send(socketfd, msg, strlen(msg), 0);

    // receive response from server
    char buffer[1024];
    recv(socketfd, buffer, 1024, 0);

    printf("Response was: %s\r\n", buffer);

    close(socketfd);

    return 0;
}

