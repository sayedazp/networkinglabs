#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define _XOPEN_SOURCE 700

void read_childproc();

int main(int argc, char* argv[])
{
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;

    pid_t pid;
    struct sigaction act;
    socklen_t adr_sz;
    int str_len, state;
    char buf[30];

    act.sa_handler = 0;
    if (argc != 2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    act.sa_handler = read_childproc;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    state = sigaction(SIGCHLD, &act, 0);
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));
    if (bind(serv_sock, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) != 0)
        printf("err");
    if (listen(serv_sock, 5) == -1)
        printf("err2");
    
    while (1)
    {
        /* code */
        adr_sz = sizeof(clnt_adr);
        clnt_sock = accept(serv_sock, (struct sockaddr *) &clnt_adr, &adr_sz);
        if (clnt_sock == -1)
            continue;
        else
            puts("new client connected");
        pid = fork();
        if (pid == -1)
        {
            puts("fork failed");
            continue;
        }if (pid == 0)
        {
           close(serv_sock);
            while ((str_len = read(clnt_sock, buf, 30))!= 0)
            {
                write(clnt_sock, buf, str_len);
                printf("client said %s\n", buf);
            }
            close(clnt_sock);
            puts("client disconnected");
            return (0);
        }
        else
        {
            close(clnt_sock);
        }
    }

    close(serv_sock);
}

void read_childproc(int sig)
{
    pid_t pid;
    int status;
    pid = waitpid(-1, &status, WNOHANG);
    printf("removed proc id %d\n", pid);
}
