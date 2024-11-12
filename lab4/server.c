#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int port = atoi(argv[1]);
    int sockfd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t cli_len = sizeof(cli_addr);
    char buffer[1024];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);  // UDP socket
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", port);

    while (1) {
        memset(buffer, 0, 1024);
        int n = recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *) &cli_addr, &cli_len);
        if (n < 0) {
            perror("Receive failed");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
        buffer[n] = '\0';
        printf("Client [%s:%d]: %s\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), buffer);
        if (strcmp(buffer, "close") == 0) {
            printf("Client requested to close the connection.\n");
            break;
        }

        printf("Enter message to client: ");
        fgets(buffer, 1024, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        n = sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *) &cli_addr, cli_len);
        if (n < 0) {
            perror("Send failed");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
    }

    close(sockfd);
    return 0;
}
