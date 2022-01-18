/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 14:12:59 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/01/18 11:56:05 by csteenvo      ########   odam.nl         */
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
	static char	buf[65536];
	static char	*ptr = buf;
	static int	bit = 0;

	(void) ctx;
	if (sig == SIGUSR2)
		*ptr |= 1 << bit;
	else
		*ptr &= ~(1 << bit);
	bit = (bit + 1) % 8;
	if (bit == 0)
	{
		if (!*ptr)
		{
			write(STDOUT_FILENO, buf, ptr - buf);
			ptr = buf;
		}
		else if (ptr == buf + sizeof(buf) - 1)
		{
			write(STDOUT_FILENO, buf, sizeof(buf));
			ptr = buf;
		}
		else
		{
			ptr += 1;
		}
	}
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
		;
}
