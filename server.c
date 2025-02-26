/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:34:49 by dsemenov          #+#    #+#             */
/*   Updated: 2025/02/24 18:06:55 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/ft_printf.h"
#include "./libft/libft.h"
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void	handler(int signo, siginfo_t *info, void *context)
{
	static unsigned char	byte = 0;
	static int				bit_count = 0;

	(void)context;
	if (signo == SIGUSR1)
		byte = (byte << 1) | 1;
	else if (signo == SIGUSR2)
		byte <<= 1;
	bit_count++;
	if (bit_count == 8)
	{
		if (byte == 0)
			kill(info->si_pid, SIGUSR2);
		ft_putchar(byte);
		byte = 0;
		bit_count = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;
	pid_t				pid;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pid = getpid();
	ft_printf("%d\n", pid);
	while (1)
		pause();
	return (0);
}
