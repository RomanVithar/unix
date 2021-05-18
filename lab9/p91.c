#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

void error (const char *msg){
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    int clie_sockfd, n;
    char buffer[256];

    struct sockaddr_in serv_addr;
    struct hostent *server;

    clie_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server = gethostbyname("127.0.0.1");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *) & serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(3425);
    if(connect(clie_sockfd, (struct sockaddr *)  &serv_addr, sizeof(serv_addr))<0) {
        error("Error"); 
    }
    printf("Enter message: ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);
    n = write(clie_sockfd, buffer, strlen(buffer));
    if(n<0){
        error("error"); 
    }  
    bzero(buffer, 256);
    n = read(clie_sockfd, buffer, 255);
    if(n<0){
        error("error"); 
    }
    printf("%s\n", buffer);
    close(clie_sockfd);
    return 0;
}
