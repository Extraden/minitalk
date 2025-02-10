#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include "./libft/libft.h"

int main(int argc, char **argv)
{
  if (argc != 3)
  {
    printf("Wrong number of arguments!\n");
    return (1);
  }
  size_t  i;
  int  j;
  unsigned char bit;
  unsigned char *msg;
  pid_t server_pid;

  server_pid = ft_atoi(argv[1]);
  msg = (unsigned char *)argv[2];
  i = 0;
  while (msg[i])
  {
    unsigned char byte = msg[i];
    j = 7;
    while (j >= 0)
    {
      bit = byte >> j & 1;
      if (bit == 1)
        kill(server_pid, SIGUSR1);
      else
        kill(server_pid, SIGUSR2); 
      usleep(1000);
      j--;
    }
    i++;
  }
  return (0);
}
