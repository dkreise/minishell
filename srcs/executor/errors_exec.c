/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:26:29 by dkreise           #+#    #+#             */
/*   Updated: 2024/02/04 12:35:49 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_tokens(t_tokens *tokens, int type)
{
	free_tok(&(tokens->first_tok));
	free(tokens->toks);
	if (type == EXP)
	{
		free_paths(tokens);
	}
}

void	exit_error(char *arg, char *msg, t_tokens *tokens, t_cmd *cmd)
{
	int	exit_code;

	exit_code = cmd->exit_code;
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
	if (exit_code == 127)
	{
		free_paths(tokens);
		free_cmd(&cmd);
		exit(exit_code);
	}
}
