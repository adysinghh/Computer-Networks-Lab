#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    
    // Creating socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation error\n");
        return -1;
    }

    // Define the server address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 address from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("Invalid address/ Address not supported\n");
        return -1;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection Failed\n");
        return -1;
    }

    // Two-way communication with the server
    while (1) {
        // Send message to the server
        printf("Client: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        send(sock, buffer, strlen(buffer), 0);

        if (strcmp(buffer, "exit\n") == 0) {
            printf("Client disconnected.\n");
            break;
        }

        // Receive message from the server
        memset(buffer, 0, BUFFER_SIZE);  // Clear buffer before receiving
        int valread = read(sock, buffer, BUFFER_SIZE);
        if (valread == 0) {
            printf("Server disconnected.\n");
            break;
        }
        printf("Server: %s\n", buffer);
        memset(buffer, 0, BUFFER_SIZE);
    }

    close(sock);
    return 0;
}
