#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8000

// Comparator function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    
    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Configure the address structure
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP
    address.sin_port = htons(PORT);

    // Bind the socket to the specified port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Start listening for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    // Accept a client connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Receive the size of the array
    int array_size;
    if (recv(new_socket, &array_size, sizeof(array_size), 0) <= 0) {
        perror("Failed to receive array size");
        close(new_socket);
        return 1;
    }

    printf("Array size received: %d\n", array_size);

    // Receive the array
    int arr[array_size];
    if (recv(new_socket, arr, sizeof(int) * array_size, 0) <= 0) {
        perror("Failed to receive array");
        close(new_socket);
        return 1;
    }

    printf("Array received: ");
    for (int i = 0; i < array_size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Sort the array
    qsort(arr, array_size, sizeof(int), compare);

    // Send the sorted array back to the client
    if (send(new_socket, arr, sizeof(int) * array_size, 0) <= 0) {
        perror("Failed to send sorted array");
        close(new_socket);
        return 1;
    }

    printf("Sorted array sent back to client.\n");

    close(new_socket);
    close(server_fd);
    return 0;
}
