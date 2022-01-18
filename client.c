/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 14:12:44 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/01/18 11:56:20 by csteenvo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

static const char	*g_msg;

static void
	check(int code)
{
	if (!code)
		exit(EXIT_FAILURE);
}

static void
	send_next(int pid)
{
	static int	bit_index = 0;
	static int	end = 0;
	int			bit;

	if (end)
		exit(EXIT_SUCCESS);
	bit = *g_msg >> bit_index & 1;
	bit_index = (bit_index + 1) % 8;
	if (bit_index == 0)
	{
		end = !*g_msg;
		g_msg += 1;
	}
	if (bit)
		check(kill(pid, SIGUSR2) == 0);
	else
		check(kill(pid, SIGUSR1) == 0);
}

static void
	handler(int sig, siginfo_t *info, void *ctx)
{
	(void) sig;
	(void) ctx;
	send_next(info->si_pid);
}

int
	main(int argc, char **argv)
{
	struct sigaction	act;
	int					pid;

	check(argc == 3);
	pid = ft_atoi(argv[1]);
	g_msg = argv[2];
	sigemptyset(&act.sa_mask);
	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO | SA_NODEFER;
	check(sigaction(SIGUSR1, &act, NULL) == 0);
	send_next(pid);
	while (1)
		;
}
