#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include "./libft/ft_printf.h"
#include "./libft/libft.h"

extern int g_pid;

void  send_msg(char c, pid_t server_pid)
{
  int  i;
  unsigned char bit;

 
    unsigned char byte = c;
    i = 7;
    while (i >= 0)
    {
      bit = byte >> i & 1;
      if (bit == 1)
        kill(server_pid, SIGUSR1);
      else
        kill(server_pid, SIGUSR2);
      usleep (5000);
      i--;
    }
}

void send_strlen(size_t len, pid_t server_pid)
{
  int i;
  unsigned char bit;

  i = 31;
  while (i >= 0)
  {
    bit = len >> i & 1;
    if (bit == 1)
      kill(server_pid, SIGUSR1);
    else
      kill(server_pid, SIGUSR2);
    usleep(5000);
    i--;
  }
}

int main(int argc, char **argv)
{
  pid_t server_pid;
  char *msg;
  size_t len;
  size_t i;

  if (argc != 3)
  {
    ft_printf("Wrong number of arguments!\n");
    return (1);
  }
  server_pid = ft_atoi(argv[1]);
  msg = argv[2];
  len = ft_strlen(msg);
  send_strlen(len, server_pid);
  i = 0;
  while (msg[i])
  {
    send_msg(msg[i], server_pid);
    i++;
  }
  return (0);
}
