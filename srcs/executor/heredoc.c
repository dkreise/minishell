/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:15:43 by dkreise           #+#    #+#             */
/*   Updated: 2024/01/28 19:17:27 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	do_hd(t_tokens *tokens, int i)
{
	int		hdfd[2];
	char	*line;
	char	*limiter;
	pid_t	pid;
	int		status;

	pipe(hdfd);
	limiter = tokens->toks[i]->value;
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		do_signals(HEREDOC);
		while (1)
		{
			line = readline("\033[1;33m>\033[m ");
			if (!line)
				exit(0);
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 && line[ft_strlen(limiter)] == '\0')
			{
				break;
			}
			ft_putstr_fd(line, hdfd[1]);
			ft_putstr_fd("\n", hdfd[1]);
			free(line);
		}
		close(hdfd[1]);
		close(hdfd[0]);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		tokens->toks[i]->hd_file = hdfd[0];
		close(hdfd[1]);
		if (WTERMSIG(status) == SIGINT)
		{
			printf("\n");
			return 1;
		}
	}
	return 0;
}

int	check_hd(t_tokens *tokens)
{
	int		i;
	int exit_hd;

	i = 0;
	exit_hd = 0;
	while (i < tokens->tok_cnt)
	{
		if (tokens->toks[i]->type == HEREDOC || tokens->toks[i]->type == PIPE_HEREDOC)
			exit_hd = do_hd(tokens, i);
		i ++;
	}
	return (exit_hd);
}	
