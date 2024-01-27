/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 09:42:14 by rpliego           #+#    #+#             */
/*   Updated: 2024/01/27 21:55:45 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "readline.h"
#include "minishell.h"

void	heredoc_handle(int sig)
{
	if (sig == SIGINT)
	{
		g_exit = 1;
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		printf("\n");
		//dprintf(2,"bobobbobobobobo\n");
		exit(1);
	}
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
    {
		g_exit = 1;
        printf("\n");
		rl_replace_line("", 1);
        rl_on_new_line();
        rl_redisplay();
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

void	do_signals(int	mode)
{
	//rl_catch_signals = 0;
	struct sigaction sa;

	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (mode == INTERACTIVE)
	{
		sa.sa_handler = handle_sigint;
	}
	else if (mode == HEREDOC)
	{
		sa.sa_handler = heredoc_handle;
	}
	else if (mode == NON_STANDAR)
	{
		sa.sa_handler = SIG_IGN;
	}
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

