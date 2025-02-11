#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "./libft/ft_printf.h"
#include "./libft/libft.h"
 
// int g_pid;

// void  handler(int signo, siginfo_t *info, void *context)
// {
// 	(void)info;
// 	(void)context;
// 	static unsigned char byte;
// 	static int bit_count;

//   if (signo == SIGUSR1)
// 	  byte = (byte << 1) | 1;
//   else if (signo == SIGUSR2)
//     byte <<= 1;

// 	bit_count++;

// 	if (bit_count == 8)
// 	{
// 		ft_putchar(byte);
// 		byte = 0;
// 		bit_count = 0;
//     return ;
// 	}
// }

// void  len_handler(int signo, siginfo_t *info, void *context)
// {
// 	(void)info;
// 	(void)context;
// 	static unsigned int i;
// 	static int bit_count;

//   if (signo == SIGUSR1)
// 	  i = (i << 1) | 1;
//   else if (signo == SIGUSR2)
//     i <<= 1;

// 	bit_count++;

// 	if (bit_count == 32)
// 	{
// 		ft_putnbr(i);
// 		i = 0;
// 		bit_count = 0;
//     return;
// 	}
// }

volatile sig_atomic_t g_receiving_length = 1;  // 1 - получаем длину, 0 - получаем сообщение
volatile unsigned int g_length = 0;
volatile int g_len_bit_count = 0;
volatile unsigned char g_char = 0;
volatile int g_char_bit_count = 0;

void universal_handler(int signo, siginfo_t *info, void *context)
{
    (void)info;
    (void)context;
    
    if (g_receiving_length)
    {
        // Принимаем длину (32 бита)
        g_length = (g_length << 1) | (signo == SIGUSR1 ? 1 : 0);
        g_len_bit_count++;
        if (g_len_bit_count == 32)
        {
            ft_printf("Length: %u\n", g_length);
            g_receiving_length = 0;  // переключаемся на приём сообщения
        }
    }
    else
    {
        // Принимаем символ (8 бит)
        g_char = (g_char << 1) | (signo == SIGUSR1 ? 1 : 0);
        g_char_bit_count++;
        if (g_char_bit_count == 8)
        {
            ft_putchar(g_char);
            g_char = 0;
            g_char_bit_count = 0;
        }
    }
}

int main(void)
{
    struct sigaction sa;
    pid_t pid;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = universal_handler;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    pid = getpid();
    ft_printf("%d\n", pid);
    while (1)
        pause();
    return (0);
}