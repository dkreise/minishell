/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:30:06 by dkreise           #+#    #+#             */
/*   Updated: 2024/03/23 16:48:22 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	blt_and_free(t_tokens *tokens, t_cmd *cmd)
{
	free_tok(&(tokens->first_tok));
	free(tokens->toks);
	if (cmd->exit_code != 0)
		exit(cmd->exit_code);
	if (check_blt(cmd->args[0]))
	{
		exec_blt(cmd, tokens->env, tokens->prev_exit);
		exit(cmd->exit_code);
	}
	free_env(&(tokens->env));
}

void	do_execve(t_tokens *tokens, t_cmd *cmd)
{
	char	*path;
	char	**lst_env;
	int		i;

	i = 0;
	lst_env = lst_to_arr((t_token **) NULL, tokens->env);
	do_signals(NON_STANDAR);
	blt_and_free(tokens, cmd);
	execve(cmd->args[0], cmd->args, lst_env);
	if (tokens->paths)
	{
		while (tokens->paths[i])
		{
			path = ft_strjoin(ft_strjoin(tokens->paths[i], "/", NONE),
					cmd->args[0], FIRST);
			execve(path, cmd->args, lst_env);
			free(path);
			i ++;
		}
	}
	free_lst(lst_env);
	cmd->exit_code = 127;
	exit_error(cmd->args[0], "command not found\n", tokens, cmd);
}

static void	do_fork(t_tokens *tokens, pid_t *pid, t_cmd *cmd)
{
	*pid = fork();
	if (*pid == 0 && cmd->args[0])
		do_execve(tokens, cmd);
	else if (*pid == 0 && !cmd->args[0])
	{
		free_cmd(&cmd);
		exit(0);
	}
}

int	exec_cmd(t_tokens *tokens, pid_t *pid, t_cmd **cmd, int *is_first)
{
	int		i;
	t_cmd	*new_cmd;

	i = 0;
	while (i < tokens->tok_cnt)
	{
		new_cmd = init_cmd(tokens, i);
		if (tokens->error == MALLOC_ERROR)
			return (MALLOC_ERROR);
		new_cmd->prev = *cmd;
		*cmd = new_cmd;
		i += args_cnt(tokens, i);
		if (*is_first && i == tokens->tok_cnt && check_blt((*cmd)->args[0])
			&& (*cmd)->exit_code == 0)
		{
			exec_blt(*cmd, tokens->env, tokens->prev_exit);
			break ;
		}
		*is_first = 0;
		tokens->cmd_cnt ++;
		pipe_redir(tokens, *cmd, i);
		do_fork(tokens, pid, *cmd);
	}
	return (0);
}
