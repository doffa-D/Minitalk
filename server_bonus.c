/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 12:22:51 by hdagdagu          #+#    #+#             */
/*   Updated: 2022/12/22 14:45:49 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler_sv(int signal, siginfo_t *info, void *nu)
{
	static int	bit;
	static int	i;
	static int	z;
	static int	buffer[3];
	static int	old_pid;

	(void)nu;
	if (info->si_pid != old_pid)
	{
		z = 0;
		i = 0;
		bit = 0;
	}
	if (signal == SIGUSR1)
		i |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		if(i >= 0 && i <= 127)
		{
			write(1, &i, 1);
		}
		else
		{
			buffer[z++] = i;
		}
		i = 0;
		bit = 0;
		if(z == 3)
		{
			write(1,&buffer[0], 1);
			write(1,&buffer[1], 1);
			write(1,&buffer[2], 1);
			z = 0;
		}
		kill(info->si_pid, SIGUSR1);
	}
	old_pid = info->si_pid;
}

void	config_signal(void)
{
	struct sigaction	sig;

	sig.sa_sigaction = &handler_sv;
	sig.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sig, NULL) == -1)
		print_error("Failed in SIGUSR1\n");
	if (sigaction(SIGUSR2, &sig, NULL) == -1)
		print_error("Failed in SIGUSR2\n");
}

int	main(int ac, char **av)
{
	ft_printf("PID :[%d]\n", getpid());
	while (1)
	{
		config_signal();
		pause();
	}
	return (0);
}
