/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 14:12:59 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/01/18 13:50:36 by csteenvo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

static void
	check(int code)
{
	if (!code)
		exit(EXIT_FAILURE);
}

static void
	handler(int sig, siginfo_t *info, void *ctx)
{
	static char	byte = 0;
	static int	bit_index = 0;

	(void) ctx;
	byte = byte << 1 | sig - SIGUSR1;
	bit_index = (bit_index + 1) % 8;
	if (bit_index == 0)
		ft_putchar_fd(byte, STDOUT_FILENO);
	check(kill(info->si_pid, SIGUSR1) == 0);
}

int
	main(void)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO | SA_NODEFER;
	check(sigaction(SIGUSR1, &act, NULL) == 0);
	check(sigaction(SIGUSR2, &act, NULL) == 0);
	ft_putstr_fd("pid: ", STDERR_FILENO);
	ft_putnbr_fd(getpid(), STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	while (1)
		pause();
}
