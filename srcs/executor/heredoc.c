/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:15:43 by dkreise           #+#    #+#             */
/*   Updated: 2024/01/25 16:57:21 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	do_hd(t_tokens *tokens, int i)
{
	int		hdfd[2];
	char	*line;
	char	*limiter;

	pipe(hdfd);
	limiter = tokens->toks[i]->value;
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
}

int	check_hd(t_tokens *tokens)
{
	int		i;
	pid_t	pid;
	int		status;

	i = 0;
	pid = fork();
	if (pid == 0)
	{
		while (i < tokens->tok_cnt)
		{
			if (tokens->toks[i]->type == HEREDOC || tokens->toks[i]->type == PIPE_HEREDOC)
				do_hd(tokens, i);
			i ++;
		}
	}
	if (pid != 0)
		waitpid(pid, &status, 0);
	return (0);
}
