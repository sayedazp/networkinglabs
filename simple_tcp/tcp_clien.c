#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int sock;
    struct sockaddr_in servaddr;
    char buf[100];

    // create
    int sock1 = socket(AF_INET, SOCK_STREAM, 0);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    // creation
    if(sock == -1)
    {
        printf("failed\n");
        exit(1);
    }else
    {
        printf("socket: %d\n", sock);
    }
    // connecting
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(4444);
    if(connect(sock, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0)
    {
        printf("failed to connect\n");
        exit(1);
    }
    else{
        printf("connection was established\n");
    }

    // reading
    int x = read(sock, buf, 100);
    printf("recieved %s\n", buf);
    // closing
    close(sock);
    printf("sock closed\n");
}