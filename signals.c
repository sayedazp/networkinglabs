#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void timeout(int sig)
{
    if (sig == SIGALRM)
        printf("time out\n");
    alarm(2);
}

void keypress(int sig)
{
    if (sig == SIGINT)
        printf("ctrl + c pressed\n");
}
int main(void)
{
    int i;
    signal(SIGALRM, timeout);
    signal(SIGINT, keypress);
    alarm(2);
    
    for (i = 0; i < 3; i++)
    {
        printf("waiting for ....\n");
        sleep(1000);
    }
}