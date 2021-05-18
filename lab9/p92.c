#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

void error (const char *msg){
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]){
    int serv_sockfd, clie_sockfd;
    socklen_t clilen;
    char buffer[256] ;
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    serv_sockfd = socket (AF_INET, SOCK_STREAM, 0) ;
    bzero ((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(3425) ;
    if (bind(serv_sockfd, (struct sockaddr *) &serv_addr,
                sizeof(serv_addr)) < 0){
        error ("Error");
    }
    listen(serv_sockfd, 1);
    clilen = sizeof(cli_addr);
    clie_sockfd = accept(serv_sockfd, (struct sockaddr *) &cli_addr,
            &clilen) ;
    bzero (buffer, 256) ;
    n = read(clie_sockfd, buffer, 255) ;
    if (n < 0)
        error("error");
    printf("Message: %s\n", buffer);
    n = write (clie_sockfd, "I got your message", 18);
    if (n < 0)
        error("error");
    close (clie_sockfd) ;
    close (serv_sockfd) ;
    return 0;
}
