/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 19:11:52 by dkreise           #+#    #+#             */
/*   Updated: 2024/02/01 13:57:04 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	args_cnt(t_tokens *tokens, int i)
{
	int	cnt;

	cnt = 0;
	while (i < tokens->tok_cnt)
	{
		if (tokens->toks[i]->type < PIPE)
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
	cmd->exit_code = 0;
}

void	init_cmd_args(t_tokens *tokens, t_cmd *cmd, int i)
{
	int	j;

	j = 0;
	while (i < tokens->tok_cnt)
	{
		if (tokens->toks[i]->type == NONE)
		{
			cmd->args[j] = ft_strdup(tokens->toks[i]->value);
			if (cmd->args[j] == NULL)
			{
				malloc_error(NULL, tokens);
				return ;
			}
			j ++;
		}
		else if (tokens->toks[i]->type >= PIPE)
			break ;
		else if (tokens->toks[i]->type > NONE && tokens->toks[i]->type < PIPE)
			do_redir(tokens, cmd, i);
		i ++;
	}
}

t_cmd	*init_cmd(t_tokens *tokens, int i)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
	{
		malloc_error(NULL, tokens);
		return (cmd);
	}
	init_flgs_cmd(cmd);
	if (tokens->toks[i]->type >= PIPE)
		tokens->toks[i]->type -= PIPE;
	cmd->args = ft_calloc(args_cnt(tokens, i) + 1, sizeof(char *));
	if (cmd->args == NULL)
	{
		malloc_error(NULL, tokens);
		return (cmd);
	}
	init_cmd_args(tokens, cmd, i);
	return (cmd);
}
