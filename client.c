#include <unistd.h>
#include <stdio.h>
#include <signal.h>

int main(void)
{
 int i;
 unsigned char bit;

 i = 7;
 unsigned char byte = 255;
 while (i >= 0)
  {
    bit = byte >> i & 1;
    if (bit == 1)
      kill(getpid(), SIGUSR1);
    else
      kill(getpid(), SIGUSR2); 
    usleep(100);
    i--;
  }
  return (0);
}
