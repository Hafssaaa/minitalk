/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 22:30:37 by hherba            #+#    #+#             */
/*   Updated: 2022/06/03 21:51:13 by hherba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

pid_t	getpid(void);
void	ft_putchar(char c);
void	ft_putnbr(int nb);

pid_t	g_clientpid = -1;

void	rec(int n, int pid)
{
	int				shift;
	static int		i = 7;
	static char		c = 0;

	if (i == -1 || pid != g_clientpid)
	{
		i = 7;
		c = 0;
		g_clientpid = pid;
	}
	shift = 1 << (i);
	if (n != 0)
		c = (c | shift);
	i--;
	if (i == -1)
		write (1, &c, 1);
}

void	server(void)
{
	int	pid;

	pid = getpid();
	ft_putnbr(pid);
	write(1, "\n", 1);
}

void	sig_handler(int sig, siginfo_t *info, void *ptr)
{
	(void)ptr;
	if (sig == SIGUSR1)
		rec(1, info->si_pid);
	else
		rec(0, info->si_pid);
}

int	main(void)
{
	struct sigaction	act;

	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = sig_handler;
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	server();
	while (1)
		pause();
	return (0);
}
