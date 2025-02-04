#include <sys/types.h>
#include <unistd.h>
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

int main(int argc, char **argv)
{
    unsigned char *msg;
    unsigned char byte;
    pid_t pid;
    
    pid = getpid();
    printf("%d\n", pid);
    char bits[8] = {0, 1, 0, 0, 0, 0, 0, 1};
    byte = bits_to_byte(bits);
    printf("%c %d\n", byte, byte);
    msg = (unsigned char *) argv[1];
    return (0);
}
