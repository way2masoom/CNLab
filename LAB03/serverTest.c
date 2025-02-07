// Crating a TCP Socket Program using c
// Server code
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netdb.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

// Main Program
int main(int argc, char *argv[]){
    int sockfd, newsockfd, portno, clilen;
    char buffer[256];
    struct sockaddr_in_serv_addr_, Cli_addr;
    int n;
    port 5001;
    
    // first call to socket() function 
    sockfd=socket(AF_INET, SOCK_STREAM,0);
    if(sockfd<0){
        perror("Error opening socket");
        exit(1);
    }

    // -- Configure setting of the server address structure 

    // Initialize Socket Structure elements to zero
    bzero((char *)&serv_addr, sizeof(serv_addr));

    // set address family = Internet
    serv_addr.sin_family=AF_INET;

    // Set Ip address to localHost
    // serv_addr.sin_addr.s_add=INADDR_ANY;
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

    // Set port Number, Using  htons function to use proper byte order
    serv_addr.sin_port=htons(portno);

    //Now Start listening for Clients, Here process will  go in sleep mode and will wait for the incoming connection
    

}