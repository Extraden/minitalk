#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

pid_t getpid(void);

unsigned char bits_to_byte(char *bits)
{

  unsigned char byte = 0;
  int i = 0;

  while (i < 8)
  {
    byte = (byte << 1) | bits[i];
    i++;
  }
  return (byte);
}

int main(void)
{
    unsigned char *msg;
    unsigned char byte;
    pid_t pid;
    unsigned char *tmp;
    
    pid = getpid();
    printf("%d\n", pid);
    tmp = bits_to_byte("01100001");
    printf("%c\n", tmp);
    return (0);
}