#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[1024];
    
    //  socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }



    // server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(5093);

    // bind socket to address and port
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }



    // incoming 
    if (listen(server_fd, 5) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }



    printf("Server is listening on port 12345...\n");

    // accept connection
    client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
    if (client_fd < 0) {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }



    // receive from client
    memset(buffer, 0, sizeof(buffer));
    recv(client_fd, buffer, sizeof(buffer), 0);
    printf("Received from client: %s\n", buffer);

    // send to client
    const char *response = "Hello from the server!";
    send(client_fd, response, strlen(response), 0);

    // close 
    close(client_fd);
    close(server_fd);


    return 0;
}