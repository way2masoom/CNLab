#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 4000

// Function to handle communication with a client
void *handle_client(void *client_socket) {
    int sock = *(int*)client_socket;
    char name[20];
    int salary, da_salary, hra_salary;

    // Receive the client's name
    int name_received = recv(sock, name, sizeof(name) - 1, 0);
    if (name_received > 0) {
        name[name_received] = '\0';
        printf("Received name from client: %s\n", name);

        // Prepare acknowledgment message
        char ack[100];  // Sufficient buffer size to hold full message
        snprintf(ack, sizeof(ack), "Hello %s, your connection is successful!", name);
        send(sock, ack, strlen(ack), 0);

        // Receive the basic salary from the client
        int bytes_received = recv(sock, &salary, sizeof(salary), 0);
        if (bytes_received > 0) {
            printf("Received Basic Salary from client: %d\n", salary);

            // Calculate DA (50% of basic salary) and HRA (15% of basic salary)
            da_salary = (salary * 50) / 100;
            hra_salary = (salary * 15) / 100;

            // Send the calculated DA and HRA back to the client
            send(sock, &da_salary, sizeof(da_salary), 0);
            send(sock, &hra_salary, sizeof(hra_salary), 0);

            printf("Sent DA: %d and HRA: %d to the client\n", da_salary, hra_salary);
        } else {
            perror("Failed to receive basic salary");
        }
    } else {
        perror("Failed to receive name");
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

    // Define server address
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
