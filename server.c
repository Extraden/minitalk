#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

pid_t getpid(void);

int main(int argc, char **argv)
{
    int i;
    int bit;
    unsigned char *msg;
    unsigned char mask;
    unsigned char byte;
    pid_t pid;
    
    pid = getpid();
    printf("%d\n", pid);
    msg = (unsigned char *) argv[1];
    mask = 1;
    i = 0;
    bit = 0;
    while (msg[i])
    {
        byte = msg[i];
        while (bit < 8)
        {
            if (byte & (mask << bit))
                printf("1");
            else
                printf("0");
            bit++;
        }
        i++;
    }
    return (0);
}