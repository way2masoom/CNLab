#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/types.h>


int main(){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0); // socket file descriptor
    printf("The Socket value is %d\n", sockfd);
    if(sockfd == -1){
        perror("Socket creation failed");
        exit(0);
    }
    
    struct sockaddr_in server, client;
    server.sin_port = htons(4000);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    int b = bind(sockfd, (struct sockaddr*)&server, sizeof(server));
    
    if(b == -1){
    	perror("Binding Failed");
    	exit(0);
    }
    printf("b = %d\n", b);

    int l = listen(sockfd, 5);
    if(l == -1){
        perror("Listening problem");
        exit(0);
    }
    printf("Succesfully listening\n");
    int size  = sizeof(client);
    int clientfd =  accept(sockfd, (struct sockaddr *) &client, &size);
    if(clientfd == -1){
        perror("Cannot connect to cient");
        exit(0);
    }
    printf("Client fd : %d\n", clientfd);
    printf("client ip is : %s\n", inet_ntoa(client.sin_addr));
    char name[20];
    int size1 = recv(clientfd, name, sizeof(name), 0);
    name[size1] = '\0';
    printf("Data received from client is: %s\n", name);
    send(clientfd, name, strlen(name), 0);

    // int x, y;
    // recv(clientfd, &x, sizeof(x), 0);
    // recv(clientfd, &y, sizeof(x), 0);

    // printf("Received value : x = %d, y = %d\n", x, y);

    // int sum = x + y;

    // printf("Sending the sum...\n");
    // send(clientfd, &sum, sizeof(sum), 0);
    // printf("Succesfully Send the sum\n");


    return 0;

    
}