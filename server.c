#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include "./printf/ft_printf.h"

void  handler(int signo, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	static unsigned char byte = 0;
	static int bit_count = 0;

  if (signo == SIGUSR1)
	byte = (byte << 1) | 1;
  else if (signo == SIGUSR2)
    byte = (byte << 1) | 0;

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
  struct sigaction sa;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_SIGINFO;
  sa.sa_sigaction = handler;
  sigaction(SIGUSR1, &sa, NULL);
  sigaction(SIGUSR2, &sa, NULL);
    pid_t pid;
    
    pid = getpid();
    ft_printf("%d\n", pid);
    while (1)
    {
      pause();
    }
    return (0);
}