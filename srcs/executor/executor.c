/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:36:27 by dkreise           #+#    #+#             */
/*   Updated: 2024/01/29 11:32:41 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// cat < tst.txt >> outptttt | ls
t_tokens test_struct(void)
{
	t_token *t1;
	t_token *t2;
	t_token *t3;
	t_token *t4;
	// t_token *t5;
	t_tokens tokens;

	t1 = new_token("cat", 0);
	t2 = new_token("tst.txt", 1);
	t3 = new_token("outputttt", 4);
	t4 = new_token("ls", 5);
	// t4 = new_token("bb", 0);
	// t5 = new_token("cat", 5);
	t1->next = t2;
	t2->next = t3;
	t3->next = t4;
	//t4->next = t5;
	tokens.tok_cnt = 4;
	tokens.first_tok = t1;
	tokens.toks = tok_to_lst(t1, tokens.tok_cnt);
	return (tokens);
}

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

void	do_execve(t_tokens *tokens, t_cmd *cmd)
{
	char	*path;
	int		i;

	i = 0;
	do_signals(NON_STANDAR);
	free_tok(&(tokens->first_tok));
	free(tokens->toks);
	if (cmd->exit_code != 0)
		exit(cmd->exit_code);
	if (check_blt(cmd->args[0]))
	{
		// change arg of exec_blt to whole cmd to be able to set exit in err case
		exec_blt(cmd->args, tokens->env);
		exit(cmd->exit_code); 
	}
	execve(cmd->args[0], cmd->args, lst_to_arr((t_token **)NULL, tokens->env));
	if (!tokens->paths)
		dprintf(2, "paths are null\n");
	if (tokens->paths)
	{
		while (tokens->paths[i])
		{
			path = ft_strjoin(ft_strjoin(tokens->paths[i], "/", NONE),
					cmd->args[0], FIRST);
			// malloc protection
			//dprintf(2, "path: %s\n", path);
			execve(path, cmd->args, lst_to_arr((t_token **)NULL, tokens->env));
			free(path);
			i ++;
		}
	}
	cmd->exit_code = 127;
	exit_error(cmd->args[0], "command not found\n", tokens, cmd);
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

int	executor(t_tokens *tokens)
{
	int		i;
	pid_t	pid;
	t_cmd	*cmd;
	t_cmd	*new_cmd;
	int		is_first;
	int		exit_hd;

	i = 0;
	is_first = 1;
	cmd = NULL;
	exit_hd = check_hd(tokens);
	if (exit_hd == 0)
	{
		while (i < tokens->tok_cnt)
		{
			new_cmd = init_cmd(tokens, i);
			if (tokens->error == MALLOC_ERROR)
				return (MALLOC_ERROR);
			new_cmd->prev = cmd;
			cmd = new_cmd;
			i += args_cnt(tokens, i);
			if (cmd->exit_code == 1)
				continue ;
			if (is_first && i == tokens->tok_cnt && check_blt(cmd->args[0]))
			{
				is_first = 0;
				exec_blt(cmd->args, tokens->env);
				break ;
			}
			tokens->cmd_cnt ++;
			pipe_redir(tokens, cmd, i);
			pid = fork();
			if (pid == 0 && cmd->args[0])
				do_execve(tokens, cmd);
			else if (pid == 0 && !cmd->args[0])
				exit(0);
		}
		wait_process(cmd, pid, tokens->cmd_cnt);
	}
	dup2(tokens->initfd[0], STDIN_FILENO);
	dup2(tokens->initfd[1], STDOUT_FILENO);
	close(tokens->initfd[0]);
	close(tokens->initfd[1]);
	if (exit_hd == 1)
		return 1;
	return (cmd->exit_code);
}
