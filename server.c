/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 14:12:59 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/01/17 16:21:01 by csteenvo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

static void
	check(int code)
{
	if (code < 0)
		exit(EXIT_FAILURE);
}

static void
	handler(int sig, siginfo_t *info, void *ctx)
{
	static char	byte;
	static int	bit = 0;

	(void) ctx;
	byte = (byte << 1) | (sig == SIGUSR2);
	bit = (bit + 1) % 8;
	if (bit == 0)
		ft_putchar_fd(byte, STDOUT_FILENO);
	check(kill(info->si_pid, SIGUSR1));
}

int
	main(void)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO | SA_NODEFER;
	check(sigaction(SIGUSR1, &act, NULL));
	check(sigaction(SIGUSR2, &act, NULL));
	ft_putstr_fd("pid: ", STDOUT_FILENO);
	ft_putnbr_fd(getpid(), STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	while (1)
		pause();
	return (0);
}
