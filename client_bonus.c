/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 12:39:40 by hdagdagu          #+#    #+#             */
/*   Updated: 2022/12/21 18:28:32 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_sig_counter;

void	count(int sig, siginfo_t *info, void *no)
{
	(void)*info;
	(void)*no;
	if (sig == SIGUSR1)
		g_sig_counter++;
}

int	checkarg(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 3)
		print_error("Invalid number of arguments\n");
	while (argv[1][i])
	{
		if (ft_isdigit(argv[1][i]) != 1)
			print_error("Invalid PID");
		i++;
	}
	if (argv[2][0] == 0)
		print_error("Invalid message (empty)\n");
	return (0);
}

void	send_mesg(char things, int pid)
{
	struct sigaction	sig;
	int					bit;

	sig.sa_sigaction = &count;
	sig.sa_flags = SA_SIGINFO;
	bit = 0;
	while (bit < 8)
	{
		if ((things & (1 << bit)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		bit++;
		usleep(100);
		sigaction(SIGUSR1, &sig, NULL);
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	int	i;

	i = 0;
	checkarg(argc, argv);
	while (argv[2][i])
	{
		send_mesg(argv[2][i], ft_atoi(argv[1]));
		i++;
	}
	if (g_sig_counter == i)
		ft_printf("\n \033[0;32mMessage has been sucessfully receieved![✔️]\n");
	return (0);
}
