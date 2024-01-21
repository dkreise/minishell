/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:44:44 by rpliego           #+#    #+#             */
/*   Updated: 2024/01/20 19:53:16 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_header(void)
{
	printf("%s           _       _     _          _ _ \n", F);
	printf("%s _ __ ___ (_)_ __ (_)___| |__   ___| | |\n", F);
	printf("%s| '_ ` _ || | '_ `| / __| '_ ` / _ | | |\n", F);
	printf("%s| | | | | | | | | | |__ | | | |  __/ | |\n", F);
	printf("%s|_| |_| |_|_|_| |_|_|___/_| |_||___|_|_|\n\n\n", F);
}

t_env	*dup_env(char **env_array)
{
	t_env *first;
	t_env *env;
	t_env *new;
	int	i;

	first = malloc(sizeof(t_env));
	if (!first)
		return (NULL);
	first->data = ft_strdup(env_array[0]);
	first->unset_flag = 0;
	first->next = NULL;
	env = first;
	i = 0;
	while (env_array[++i] != NULL)
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (NULL);
		new->data = ft_strdup(env_array[i]);
		new->unset_flag = 0;
		new->next = NULL;
		env->next = new;
		env = new;
	}
	return (first);
}

int	check_blt(char *cmd, t_env *env)
{
	(void)env;
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (0);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (0);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (0);
	return (1);
}

void	exec_blt(char **cmd, t_env *env, int exit_code)
{
	if (ft_strncmp(cmd[0], "env", 4) == 0)
		ft_env(env);
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
		ft_export(cmd, &env);
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		ft_unset(cmd, &env);
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(cmd[0], "cd", 3) == 0)
		ft_cd(cmd, env);
	else if (ft_strncmp(cmd[0], "exit", 6) == 0)
		ft_exit(cmd, env, exit_code);
	else if (ft_strncmp(cmd[0], "echo", 5) == 0)
		ft_echo(cmd);
}

int main(int ac, char **av , char **enviroment)
{
	char *line;
	t_env *env;
	char **test;
	int		exit_code;

	(void)ac;
	(void)av;
	exit_code = 0;
	print_header();
	env = dup_env(enviroment);
	while (1)
	{
		do_signals();
		line = readline("\033[1;33mмини-оболочка-0.1$\033[m ");
		if (!line)
		{
			printf("exit\n");
			exit (0);
		}
		test = ft_split(line, ' ');
		exec_blt(test, env, exit_code);
		add_history(line);
	}
	return (0);
}
