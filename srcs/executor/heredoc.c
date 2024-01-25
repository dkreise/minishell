/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:15:43 by dkreise           #+#    #+#             */
/*   Updated: 2024/01/25 13:48:59 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	check_hd(t_tokens *tokens)
{
	int		i;
	int		hdfd[2];
	char	*line;
	char	*limiter;

	i = 0;
	do_signals(HEREDOC);
	while (i < tokens->tok_cnt)
	{
		if (tokens->toks[i]->type == HEREDOC || tokens->toks[i]->type == PIPE_HEREDOC)
		{
			pipe(hdfd);
			//protect pipe??
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
		i ++;
	}
	do_signals(INTERACTIVE);
}
