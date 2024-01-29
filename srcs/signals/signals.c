/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 09:42:14 by rpliego           #+#    #+#             */
/*   Updated: 2024/01/29 18:22:56 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "readline.h"
#include "minishell.h"

void	heredoc_handle(int sig, siginfo_t *data, void *non_used_data)
{
	(void) data;
	(void) non_used_data;
	if (sig == SIGINT)
	{
		g_exit = 1;
		printf("\n\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		exit(1);
	}
}

void	handle_sigint(int sig, siginfo_t *data, void *non_used_data)
{
	(void)data;
	(void)non_used_data;
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_exit = 1;
	}
}

void	do_sigign(int signum)
{
	struct sigaction	signal;

	signal.sa_handler = SIG_IGN;
	signal.sa_flags = SA_RESTART;
	sigemptyset(&signal.sa_mask);
	if (sigaction(signum, &signal, NULL) < 0)
		exit (1);
}

void	signals_print_handler(void)
{
	struct termios	tc;

	tcgetattr(0, &tc);
	tc.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &tc);
}

void	do_signals(int mode)
{
	struct sigaction	signal;

	signal.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset(&signal.sa_mask);
	signals_print_handler();
	if (mode == INTERACTIVE)
		signal.sa_sigaction = handle_sigint;
	if (mode == HERDOC)
		signal.sa_sigaction = heredoc_handle;
	sigaction(SIGINT, &signal, NULL);
	sigaction(SIGQUIT, &signal, NULL);
	return ;
}
