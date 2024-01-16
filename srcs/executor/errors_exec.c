/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:26:29 by dkreise           #+#    #+#             */
/*   Updated: 2024/01/16 17:04:09 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*cur;
	t_cmd	*freed;
	int		i;

	cur = cmd;
	i = 0;
	while (cur)
	{
		while (cur->args[i])
		{
			free(cur->args[i]);
			i ++;
		}
		free(cur->args);
		freed = cur;
		cur = cur->prev;
		free(freed);
	}
}

// void	free_tokens(t_tokens *tokens)
// {

// }

void	exit_error(char *arg, char *msg, t_tokens *tokens, t_cmd *cmd)
{
	(void)tokens;
	write(2, "minishell: ", ft_strlen("minishell: "));
	if (msg)
	{
		if (arg)
		{
			write(2, arg, ft_strlen(arg));
			write(2, ": ", 2);
		}
		write(2, msg, ft_strlen(msg));
	}
	else
		perror(arg);
	if (cmd->exit_code > 0)
	{
		//free tokens and cmd
		//free(cmd);
		exit(cmd->exit_code);
	}
}
