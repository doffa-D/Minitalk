/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 12:22:51 by hdagdagu          #+#    #+#             */
/*   Updated: 2022/12/20 18:20:34 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler_sv(int signal, siginfo_t *info, void *nu)
{
	static int	bit;
	static int	i;
	static int	old_pid;

	(void)nu;
	if (info->si_pid != old_pid)
		bit = 0;
	if (signal == SIGUSR1)
		i |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		write(1, &i, 1);
		i = 0;
		bit = 0;
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
