// client.c
// This is a client program that connects to a server, sends a string, then prints the reversed string received from the server.

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include<string.h>
 
int main(int argc,char **argv) {
    int sockfd;
    char sendline[100];
    strncpy(sendline, argv[1], sizeof(sendline) - 1);
    char recvline[100];
    struct sockaddr_in servaddr;
 
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof servaddr);
 
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(31415);
 
    inet_pton(AF_INET,"127.0.0.1",&(servaddr.sin_addr));
    
    // Connect to the server
    connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

    // Clear the receive buffer
    bzero(recvline, 100);

    // Send the string to the server and read the reversed string
    write(sockfd, sendline, strlen(sendline) + 1);
    read(sockfd, recvline, 100);
    printf("%s", recvline);
    close(sockfd);
}