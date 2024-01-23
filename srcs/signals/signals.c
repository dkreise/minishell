/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 09:42:14 by rpliego           #+#    #+#             */
/*   Updated: 2024/01/23 22:13:07 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "readline.h"
#include "minishell.h"

void	heredoc_handle(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
    {
        printf("\n");
		rl_replace_line("", 1);
        rl_on_new_line();
        rl_redisplay();
    }
}

void	stop_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	do_signals(int	mode)
{
	rl_catch_signals = 0;
	if (mode == INTERACTIVE)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	if (mode == HEREDOC)
	{
		signal(SIGINT, heredoc_handle);
		signal(SIGQUIT, SIG_IGN);
	}
}

