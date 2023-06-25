#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int servsock, clientsock;
    struct sockaddr_in servaddr, clientaddr;
    int clientaddrlen;

    servsock = socket(AF_INET, SOCK_STREAM, 0);
    // creation
    if(servsock == -1)
    {
        printf("failed\n");
        exit(1);
    }else
    {
        printf("socket: %d\n", servsock);
    }
    //binding
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(4444);
    if (bind(servsock, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0)
    {
        printf("failed to bind\n");
        exit(1);
    }else
    {
        printf("bound\n");
    }
    // listening
    if (listen(servsock, 1) != 0){
        printf("failed\n");
        exit(1);
    }else{
        printf("listening\n");
    }
    // accepting
    bzero(&clientaddr, sizeof(clientaddr));
    clientsock = accept(servsock, (struct sockaddr*)&clientaddr, &clientaddrlen);
    if (clientsock == -1)
    {
        printf("failed to accept client's req\n");
        exit(1);
    }else
    {
        "accepted";
    }
    // writing
    char *msg = "hello client";
    write(clientsock, msg, strlen(msg));
    printf("sent  %s\n", msg);
    // closing
    close(servsock);
    printf("serv socket closed\n");
    close(clientsock);    
    printf("client sock closed\n");
}
