#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8000

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation error\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("Invalid address/ Address not supported\n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection Failed\n");
        return -1;
    }

    int array_size;
    printf("Enter the size of the array: ");
    scanf("%d", &array_size);

    int arr[array_size];
    printf("Enter the elements of the array (including negative numbers):\n");
    for (int i = 0; i < array_size; i++) {
        scanf("%d", &arr[i]);
    }

    if (send(sock, &array_size, sizeof(array_size), 0) <= 0) {
        perror("Failed to send array size");
        close(sock);
        return 1;
    }

    if (send(sock, arr, sizeof(int) * array_size, 0) <= 0) {
        perror("Failed to send array");
        close(sock);
        return 1;
    }

    if (recv(sock, arr, sizeof(int) * array_size, 0) <= 0) {
        perror("Failed to receive sorted array");
        close(sock);
        return 1;
    }

    printf("Sorted array received from server: ");
    for (int i = 0; i < array_size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    close(sock);
    return 0;
}
