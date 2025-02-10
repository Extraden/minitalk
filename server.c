#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include "./libft/ft_printf.h"
#include "./libft/libft.h"
 
int g_pid;

void  handler(int signo, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	static unsigned char byte = 0;
	static int bit_count = 0;

  if (signo == SIGUSR1)
	  byte = (byte << 1) | 1;
  else if (signo == SIGUSR2)
    byte <<= 1;

	bit_count++;

	if (bit_count == 8)
	{
		write(1, &byte, 1);
		byte = 0;
		bit_count = 0;
	}
}

int main(void)
{
  struct sigaction  sa;
  pid_t pid;

  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_SIGINFO;
  sa.sa_sigaction = handler;
  sigaction(SIGUSR1, &sa, NULL);
  sigaction(SIGUSR2, &sa, NULL);
    pid = getpid();
    ft_printf("%d\n", pid);
    while (1)
    {
      pause();
    }
    return (0);
}