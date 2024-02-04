/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:36:27 by dkreise           #+#    #+#             */
/*   Updated: 2024/02/04 17:42:03 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**get_paths(t_token **tok_first, char **env, int i, int j)
{
	char	**paths;

	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) != 0)
			i ++;
		else if (ft_strncmp(env[i], "PATH", 4) == 0)
			break ;
	}
	if (env[i])
	{
		while (env[i][j] != '=' && env[i][j] != '\0')
			j ++;
		j ++;
		paths = ft_split(*(env + i) + j, ':');
		if (!paths)
		{
			malloc_error(tok_first, NULL);
			return (NULL);
		}
		return (paths);
	}
	return (NULL);
}

void	wait_process(t_cmd *cmd, pid_t pid, int cmd_cnt)
{
	int	status;

	while (cmd_cnt >= 0)
	{
		cmd_cnt --;
		if (pid == wait(&status))
		{
			if (WIFEXITED(status))
				cmd->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGINT)
					cmd->exit_code = 130;
				else if (WTERMSIG(status) == SIGQUIT)
				{
					cmd->exit_code = 131;
					printf("Quit: 3\n");
				}
			}
		}
	}
}

void	set_initfd(t_tokens *tokens)
{
	dup2(tokens->initfd[0], STDIN_FILENO);
	dup2(tokens->initfd[1], STDOUT_FILENO);
	close(tokens->initfd[0]);
	close(tokens->initfd[1]);
}

int	executor(t_tokens *tokens)
{
	pid_t	pid;
	t_cmd	*cmd;
	int		is_first;
	int		exit_exec;

	is_first = 1;
	cmd = NULL;
	exit_exec = check_hd(tokens);
	if (exit_exec == 0)
	{
		exit_exec = exec_cmd(tokens, &pid, &cmd, &is_first);
		if (exit_exec == MALLOC_ERROR)
			return (MALLOC_ERROR);
		wait_process(cmd, pid, tokens->cmd_cnt);
	}
	set_initfd(tokens);
	if (exit_exec == 1)
		return (1);
	exit_exec = cmd->exit_code;
	free_cmd(&cmd);
	return (exit_exec);
}
