#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <IP> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *ip = argv[1];
    int port = atoi(argv[2]);
    int sockfd;
    struct sockaddr_in serv_addr;
    char buffer[1024];
    socklen_t serv_len = sizeof(serv_addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);  // UDP socket
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Connected to server\n");

    while (1) {
        memset(buffer, 0, 1024);
        printf("Enter message to server: ");
        fgets(buffer, 1024, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        int n = sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *) &serv_addr, serv_len);
        if (n < 0) {
            perror("Send failed");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
        if (strcmp(buffer, "QUIT") == 0) {
            printf("Closing connection.\n");
            break;
        }

        memset(buffer, 0, 1024);
        n = recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *) &serv_addr, &serv_len);
        if (n < 0) {
            perror("Receive failed");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
        buffer[n] = '\0';
        printf("Server: %s\n", buffer);
    }

    close(sockfd);
    return 0;
}
