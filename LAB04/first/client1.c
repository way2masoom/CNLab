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
     int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("The Socket value is %d\n", sockfd);
    if(sockfd == -1){
        perror("Socket creation failed");
        exit(0);
    }
    
    struct sockaddr_in server;
    server.sin_port = htons(4000);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    int c = connect(sockfd,(struct sockaddr *) &server, sizeof(server));
    if(c == -1){                    
        perror("connection error");
        exit(0);
    }
    printf("Successful connected to server\n");
    
    char name[20];
    printf("Enter name : ");
    scanf("%s", name);
    send(sockfd, name, strlen(name), 0);

    int size1 = recv(sockfd, name, sizeof(name), 0);
    name[size1] = '\0';
     printf("Data received from server is: %s\n", name);

    // int x, y, sum;
    // printf("Enter x and y : ");
    // scanf("%d%d",&x, &y);
    // printf("Making Request to server...\n");
    // send(sockfd, &x, sizeof(x), 0);
    // send(sockfd, &y, sizeof(x), 0);
    // recv(sockfd, &sum, sizeof(sum),0);
    // printf("Sum is : %d\n", sum);
    return 0;
}