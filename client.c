#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include "./libft/ft_printf.h"
#include "./libft/libft.h"

volatile sig_atomic_t g_ack_received = 0;

void  ack_handler(int signo)
{
  (void) signo;
  g_ack_received = 1;
}

void  send_bit(unsigned char bit, pid_t server_pid)
{
  g_ack_received = 0;
  if (bit)
    kill(server_pid, SIGUSR1);
  else
    kill(server_pid, SIGUSR2);
  
  while (!g_ack_received)
    pause();
}

void  send_char(char c, pid_t server_pid)
{
  int  i;
  unsigned char bit;
  unsigned char byte;
    
  byte = c;
  i = 7;
  while (i >= 0)
  {
    bit = byte >> i & 1;
    send_bit(bit, server_pid);
    i--;
  }
}

// void send_strlen(size_t len, pid_t server_pid)
// {
//   int i;
//   unsigned char bit;

//   i = 31;
//   while (i >= 0)
//   {
//     bit = len >> i & 1;
//     if (bit == 1 && g_ack_received == 0)
//       kill(server_pid, SIGUSR1);
//     else if (bit == 0 && g_ack_received == 0)
//       kill(server_pid, SIGUSR2);
//     else
//       exit(1);
//     usleep(1000);
//     g_ack_received = 1;
//     i--;
//   }
// }


int main(int argc, char **argv)
{
  pid_t server_pid;
  char *msg;
  //size_t len;
  size_t i;
  struct sigaction  sa;

  if (argc != 3)
  {
    ft_printf("Wrong number of arguments!\n");
    return (1);
  }
  sigemptyset(&sa.sa_mask);
  sa.sa_handler = ack_handler;
  sa.sa_flags = 0;
  sigaction(SIGUSR1, &sa, NULL);
  server_pid = ft_atoi(argv[1]);
  msg = argv[2];
  //len = ft_strlen(msg);
  // send_strlen(len, server_pid);
  i = 0;
  while (msg[i])
  {
    send_char(msg[i], server_pid);
    i++;
  }
  return (0);
}
