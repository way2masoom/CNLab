#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    // Create socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Define server address
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(4000); // Server port
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP address

    // Connect to the server
    if (connect(sockfd, (struct sockaddr*)&server, sizeof(server)) == -1) {
        perror("Connection error");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("Successfully connected to server\n");

    // Send name to the server
    char name[20];
    printf("Enter name: ");
    scanf("%s", name);
    send(sockfd, name, strlen(name), 0);

    // Receive acknowledgment from server
    char ack[50];
    int size1 = recv(sockfd, ack, sizeof(ack) - 1, 0);
    if (size1 > 0) {
        ack[size1] = '\0';
        printf("Data received from server: %s\n", ack);
    }

    // Input and send basic salary to server
    int salary, da_salary, hra_salary;
    printf("Enter Basic Salary: ");
    scanf("%d", &salary);
    send(sockfd, &salary, sizeof(salary), 0);

    // Receive DA and HRA from server
    recv(sockfd, &da_salary, sizeof(da_salary), 0);
    recv(sockfd, &hra_salary, sizeof(hra_salary), 0);

    // Display the received DA and HRA
    printf("DA (50%% of Basic Salary): %d\n", da_salary);
    printf("HRA (15%% of Basic Salary): %d\n", hra_salary);

    // Close socket
    close(sockfd);
    return 0;
}
