#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8888

int main(int argc, char *argv[]) {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    int buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    int n;
    printf("Enter number of elements in array: ");
    scanf("%d", &n);

    buffer[0] = n;

    printf("Enter the elements:\n");
    for (int i = 1; i <= n; i++) {
        scanf("%d", &buffer[i]);
    }

    send(sock, buffer, (n + 1) * sizeof(int), 0);

    valread = read(sock, buffer, sizeof(buffer));

    printf("Sorted array received from server:\n");
    for (int i = 1; i <= n; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");

    close(sock);

    return 0;
}