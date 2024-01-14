/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:36:27 by dkreise           #+#    #+#             */
/*   Updated: 2024/01/14 18:25:34 by dkreise          ###   ########.fr       */
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
	while (*dup_env)
	{
		if (ft_strncmp(*dup_env, "PATH", 4) != 0)
			dup_env ++;
		else
			break ;
	}
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
	if (tokens->paths)
	{
		while (tokens->paths[i])
		{
			path = ft_strjoin(ft_strjoin(tokens->paths[i], "/", NONE),
					cmd->args[0], FIRST);
			// malloc protection
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

void	executor(t_tokens *tokens, char **env)
{
	int	i;
	int pid;
	t_cmd	*cmd;
	t_cmd	*new_cmd;

	i = 0;
	tokens->paths = get_paths(env);
	// get_paths can return NULL
	tokens->env = env;
	tokens->initfd[0] = dup(STDIN_FILENO);
	tokens->initfd[1] = dup(STDOUT_FILENO);
	cmd = NULL;
	while (i < tokens->tok_cnt)
	{
		new_cmd = init_cmd(tokens, i);
		new_cmd->prev = cmd;
		cmd = new_cmd;
		i += args_cnt(tokens, i);
		pipe_redir(tokens, cmd, i);
		if (cmd->error != 0)
			continue;
		pid = fork();
		if (pid == 0 && cmd->args[0])
			do_execve(tokens, cmd);
		else if (pid == 0 && !cmd->args[0])
			exit(0);
	}
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	//(void)env;

	t_tokens test_s = test_struct();
	executor(&test_s, env);
	return (0);
}
