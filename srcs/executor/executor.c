/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:36:27 by dkreise           #+#    #+#             */
/*   Updated: 2024/01/16 18:34:50 by dkreise          ###   ########.fr       */
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

char	**get_paths(char **env)
{
	char	**paths;
	char	**dup_env;

	dup_env = env;
	//if (!(*dup_env))
	//	dprintf(2, "*dup_env is null\n");
	while (*dup_env)
	{
		dprintf(2, "*env: %s\n", *dup_env);
		dprintf(2, "strncmp: %i\n", ft_strncmp(*dup_env, "PATH", 4));
		if (ft_strncmp(*dup_env, "PATH", 4) != 0)
			dup_env ++;
		else
			break ;
	}
	if (!(*dup_env))
		dprintf(2, "*dup_env is null\n");
	if (*dup_env)
	{
		while (**dup_env != '/' && **dup_env != '\0')
			(*dup_env)++;
		paths = ft_split(*dup_env, ':');
		if (!paths)
			return (NULL);
		return (paths);
	}
	//if (!env_start && path dont exists)
	//	*dup_env = NOENV;
	return (NULL);
}

void	do_execve(t_tokens *tokens, t_cmd *cmd)
{
	char	*path;
	int		i;

	i = 0;
	execve(cmd->args[0], cmd->args, tokens->env);
	if (!tokens->paths)
		dprintf(2, "paths are null\n");
	if (tokens->paths)
	{
		while (tokens->paths[i])
		{
			path = ft_strjoin(ft_strjoin(tokens->paths[i], "/", NONE),
					cmd->args[0], FIRST);
			// malloc protection
			dprintf(2, "path: %s\n", path);
			execve(path, cmd->args, tokens->env);
			free(path);
			i ++;
		}
	}
	cmd->exit_code = 127;
	exit_error(cmd->args[0], "command not found\n", tokens, cmd);
	//dprintf(2, "%s: command not found\n", cmd->args[0]);
	//exit(127);
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
			/*else if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGINT)
					cmd->err = 130;
				else if (WTERMSIG(status) == SIGQUIT)
				{
					cmd->err = 131;
					printf("Quit: 3\n");
				}
			}*/
		}
	}
}

void	executor(t_tokens *tokens)
{
	int		i;
	pid_t	pid;
	t_cmd	*cmd;
	t_cmd	*new_cmd;

	i = 0;

	cmd = NULL;
	if (!tokens->paths)
		dprintf(2, "paths are null\n");
	while (i < tokens->tok_cnt)
	{
		new_cmd = init_cmd(tokens, i);
		new_cmd->prev = cmd;
		cmd = new_cmd;
		i += args_cnt(tokens, i);
		tokens->cmd_cnt ++;
		pipe_redir(tokens, cmd, i);
		if (cmd->error != 0)
			continue;
		pid = fork();
		if (pid == 0 && cmd->args[0])
			do_execve(tokens, cmd);
		else if (pid == 0 && !cmd->args[0])
			exit(0);
	}
	wait_process(cmd, pid, tokens->cmd_cnt);
}

/*
int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	//(void)env;

	t_tokens test_s = test_struct();
	executor(&test_s, env);
	return (0);
}*/
