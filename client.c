/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 14:12:44 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/01/17 16:20:48 by csteenvo      ########   odam.nl         */
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
	if (code < 0)
		exit(EXIT_FAILURE);
}

static void
	send_next(int pid)
{
	static int		bit = 0;
	static size_t	index = 0;

	if (g_msg[index] == '\0')
		exit(EXIT_SUCCESS);
	if (g_msg[index] >> (7 - bit) & 1)
		check(kill(pid, SIGUSR2));
	else
		check(kill(pid, SIGUSR1));
	bit = (bit + 1) % 8;
	index += bit == 0;
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

	(void) argc;
	pid = ft_atoi(argv[1]);
	g_msg = argv[2];
	sigemptyset(&act.sa_mask);
	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO | SA_NODEFER;
	check(sigaction(SIGUSR1, &act, NULL));
	send_next(pid);
	while (1)
		pause();
}
