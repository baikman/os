#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
 
int main() {
 
    char str[100];
    int listen_fd, comm_fd, i, j;
 
    struct sockaddr_in servaddr;
 
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
 
    bzero( &servaddr, sizeof(servaddr));
 
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(31415);
 
    bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
 
    listen(listen_fd, 10);
 
    while(1) {

        comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);
        bzero(str, 100);
 
        read(comm_fd,str,100);
 
        printf("Sending reversed message back - %s",str);

        int length = strlen(str);
        int start = 0;
        int end = length - 1;
        char temp;

        while (start < end) {
            temp = str[start];
            str[start] = str[end];
            str[end] = temp;
            start++;
            end--;
        }
        
        str[length] = '\n';
        write(comm_fd, str, strlen(str)+1);
    }
}