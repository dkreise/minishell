/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:15:43 by dkreise           #+#    #+#             */
/*   Updated: 2024/01/27 21:54:30 by rpliego          ###   ########.fr       */
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
	// if (pid == -1)
	// 	return -1;
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
		tokens->toks[i]->hd_file = hdfd[0];
		close(hdfd[0]);
		exit(0);
	}
	// else
	// {
		waitpid(pid, &status, 0);
		close(hdfd[1]);
		if (WTERMSIG(status) == SIGINT)
			return 1;
		return 0;
	//}
	do_signals(INTERACTIVE);
	// tokens->toks[i]->hd_file = hdfd[0];
	// waitpid(pid, &status, 0);
	// close(hdfd[1]);
	// do_signals(INTERACTIVE);
	// if (WTERMSIG(status) == SIGINT)
	// 	return 1;
	// return 0;
}

int	check_hd(t_tokens *tokens)
{
	int		i;
	//int exit_hd;
	//pid_t	pid;
	//int		status;

	i = 0;
	//pid = fork();
	//if (pid == 0)
	//{
		while (i < tokens->tok_cnt)
		{
			if (tokens->toks[i]->type == HEREDOC || tokens->toks[i]->type == PIPE_HEREDOC)
				g_exit = do_hd(tokens, i);
			i ++;
		}
		//exit(0);
	//}
	//waitpid(pid, &status, 0);
	//do_signals(INTERACTIVE);
	return (g_exit);
}	
