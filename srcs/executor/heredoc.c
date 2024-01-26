/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:15:43 by dkreise           #+#    #+#             */
/*   Updated: 2024/01/26 13:58:18 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	do_hd(t_tokens *tokens, int i)
{
	int		hdfd[2];
	char	*line;
	char	*limiter;
	pid_t	pid;
	int		status;

	pipe(hdfd);
	limiter = tokens->toks[i]->value;
	pid = fork();
	if (pid == 0)
	{
		line = readline("\033[1;33m>\033[m ");
		if (!line)
		{
			close(hdfd[1]);
			return ;
		}
		while (ft_strncmp(line, limiter, ft_strlen(limiter)) != 0 || line[ft_strlen(limiter)] != '\0')
		{
			ft_putstr_fd(line, hdfd[1]);
			ft_putstr_fd("\n", hdfd[1]);
			free(line);
			line = readline("\033[1;33m>\033[m ");
			if (!line)
				break ;
		}
		free(line);
		close(hdfd[1]);
		tokens->toks[i]->hd_file = hdfd[0];
		close(hdfd[0]);
		exit (0);
	}
	tokens->toks[i]->hd_file = hdfd[0];
	waitpid(pid, &status, 0);
	close(hdfd[1]);
}

int	check_hd(t_tokens *tokens)
{
	int		i;
	//pid_t	pid;
	//int		status;

	i = 0;
	//pid = fork();
	//do_signals(HEREDOC);
	//if (pid == 0)
	//{
		while (i < tokens->tok_cnt)
		{
			if (tokens->toks[i]->type == HEREDOC || tokens->toks[i]->type == PIPE_HEREDOC)
				do_hd(tokens, i);
			i ++;
		}
		//exit(0);
	//}
	//if (pid != 0)
	//	waitpid(pid, &status, 0);
	//do_signals(INTERACTIVE);
	return (0);
}
