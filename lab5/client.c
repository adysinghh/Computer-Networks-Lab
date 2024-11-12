#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock_fd;
    struct sockaddr_in server_addr;
    char buffer[1024];

    // create 
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5093);
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("Invalid address");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }

    // connect
    if (connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }

    // send message
    const char *message = "Hello from the client!";
    send(sock_fd, message, strlen(message), 0);

    //  response
    memset(buffer, 0, sizeof(buffer));
    recv(sock_fd, buffer, sizeof(buffer), 0);
    printf("Received from server: %s\n", buffer);


    // close 
    close(sock_fd);

    return 0;
}