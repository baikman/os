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
 
    connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

    bzero(recvline, 100);

    write(sockfd,sendline,strlen(sendline)+1);
    read(sockfd,recvline,100);
    printf("%s",recvline);
}