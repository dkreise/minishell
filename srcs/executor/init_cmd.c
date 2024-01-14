/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 19:11:52 by dkreise           #+#    #+#             */
/*   Updated: 2024/01/14 18:21:31 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	args_cnt(t_tokens *tokens, int i)
{
	int	cnt;

	cnt = 0;
	while (i < tokens->tok_cnt)
	{
		if (tokens->toks[i]->type < 5)
			cnt ++;
		else 
			return (cnt);
		i ++;
	}
	return (cnt);
}

void	init_flgs_cmd(t_cmd *cmd)
{
	cmd->redir_in_flg = 0;
	cmd->redir_out_flg = 0;
	cmd->pipe_done_flg = 0;
	cmd->error = 0;
	cmd->exit_code = 0;
}

t_cmd	*init_cmd(t_tokens *tokens, int i)
{
	t_cmd	*cmd;
	int		j;

	cmd = malloc(sizeof(t_cmd));
	// malloc protection
	// set flags to zero
	init_flgs_cmd(cmd);
	if (tokens->toks[i]->type >= 5)
		tokens->toks[i]->type -= 5;
	cmd->args = ft_calloc(args_cnt(tokens, i) + 1, sizeof(char *));
	// malloc protection
	j = 0;
	while (i < tokens->tok_cnt)
	{
		if (tokens->toks[i]->type == 0)
		{
			cmd->args[j] = ft_strdup(tokens->toks[i]->value);
			// malloc protection
			j ++;
		}
		else if (tokens->toks[i]->type >= 5)
			break ;
		else if (tokens->toks[i]->type > 0 && tokens->toks[i]->type < 5)
			do_redir(tokens, cmd, i);
		i ++;
	}
	return (cmd);
}
