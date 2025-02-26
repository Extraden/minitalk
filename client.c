/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:34:42 by dsemenov          #+#    #+#             */
/*   Updated: 2025/02/24 18:16:34 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/ft_printf.h"
#include "./libft/libft.h"
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

volatile sig_atomic_t	g_ack_received = 0;

void	ack_handler(int signo)
{
	if (signo == SIGUSR2)
		ft_printf("The message is sent!");
	g_ack_received = 1;
}

void	send_bit(unsigned char bit, pid_t server_pid)
{
	g_ack_received = 0;
	if (bit)
		kill(server_pid, SIGUSR1);
	else
		kill(server_pid, SIGUSR2);
	while (!g_ack_received)
		pause();
}

void	send_char(char c, pid_t server_pid)
{
	int				i;
	unsigned char	bit;
	unsigned char	byte;

	byte = c;
	i = 7;
	while (i >= 0)
	{
		bit = byte >> i & 1;
		send_bit(bit, server_pid);
		i--;
	}
}

int	main(int argc, char **argv)
{
	pid_t				server_pid;
	char				*msg;
	size_t				i;
	struct sigaction	sa;

	if (argc != 3)
	{
		ft_printf("Wrong number of arguments!\n");
		return (1);
	}
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = ack_handler;
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	server_pid = ft_atoi(argv[1]);
	msg = argv[2];
	i = -1;
	while (msg[++i])
		send_char(msg[i], server_pid);
	send_char('\n', server_pid);
	send_char('\0', server_pid);
	return (0);
}
