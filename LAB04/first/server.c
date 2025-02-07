#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 4000
#define BUFFER_SIZE 1024

// Function to handle communication with a client
void *handle_client(void *client_socket) {
    int sock = *(int*)client_socket;
    char buffer[BUFFER_SIZE];
    int bytes_received;

    // Receive messages from the client continuously
    while ((bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_received] = '\0'; // Null-terminate the received string
        printf("Received from client: %s\n", buffer);

        // Echo the message back to the client
        send(sock, buffer, bytes_received, 0);
    }

    // Check if recv() returned -1
    if (bytes_received < 0) {
        perror("recv failed");
    }

    // Close the client socket and exit the thread when done
    close(sock);
    printf("Client disconnected.\n");
    return NULL;
}

int main() {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    pthread_t thread_id;

    // Create the server socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

// int x, y;
    // recv(clientfd, &x, sizeof(x), 0);
    // recv(clientfd, &y, sizeof(x), 0);

    // printf("Received value : x = %d, y = %d\n", x, y);

    // int sum = x + y;

    // printf("Sending the sum...\n");
    // send(clientfd, &sum, sizeof(sum), 0);
    // printf("Successfully Send the sum\n");


    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; // Listen on all interfaces
    server_addr.sin_port = htons(PORT);

    // Bind the socket to the specified IP and port
    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        close(server_sock);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_sock, 5) == -1) {
        perror("Listen failed");
        close(server_sock);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    // Accept connections from clients continuously
    while (1) {
        client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_addr_len);
        if (client_sock < 0) {
            perror("Accept failed");
            continue; // Continue accepting new connections
        }

        printf("Client connected from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        // Create a new thread to handle the client
        if (pthread_create(&thread_id, NULL, handle_client, (void*)&client_sock) != 0) {
            perror("Failed to create thread");
            close(client_sock); // Close client socket if thread creation fails
        }

        // Detach the thread to allow it to clean up automatically when done
        pthread_detach(thread_id);
    }

    // Close the server socket (this code will not be reached due to the infinite loop)
    close(server_sock);
    return 0;
}
