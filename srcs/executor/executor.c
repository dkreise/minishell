/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:36:27 by dkreise           #+#    #+#             */
/*   Updated: 2024/01/09 19:40:06 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tokens test_struct(void)
{
	t_token *t1;
	t_token *t2;
	t_token *t3;
	t_token *t4;
	t_token *t5;
	t_tokens tokens;

	t1 = new_token("ls", 0);
	t2 = new_token("-la", 0);
	t3 = new_token("cat", 5);
	t4 = new_token("cat", 5);
	t5 = new_token("file1", 4);
	t1->next = t2;
	t2->next = t3;
	t3->next = t4;
	t4->next = t5;
	tokens.tok_cnt = 5;
	tokens.first_tok = t1;
	tokens.toks = tok_to_lst(t1, tokens.tok_cnt);
	return (tokens);
}

char	**get_paths(char **env)
{
	char	**paths;
	char	**dup_env;

	dup_env = env;
	if (!*env)
		*dup_env = NOENV;
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
			//if (!path) --> exit_error(NULL, "memory allocation error\n", c_struct, 1);
			execve(path, cmd->args, tokens->env);
			free(path);
			i ++;
		}
	}
	printf("command not found\n");
	//exit_error(c_struct->s_argv[cmd->num], "command not found\n", c_struct, 127);
}

void	executor(t_tokens *tokens, char **env)
{
	int	i;
	t_cmd	cmd;

	i = 0;
	tokens->paths = get_paths(env);
	while (i < tokens->tok_cnt)
	{
		cmd = init_cmd(tokens, i);
		//printf("%s\n", cmd.args[0]);
		do_execve(tokens, &cmd);
		i += args_cnt(tokens, i);
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
