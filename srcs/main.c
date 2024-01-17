/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:44:44 by rpliego           #+#    #+#             */
/*   Updated: 2024/01/17 17:24:03 by dkreise          ###   ########.fr       */
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
	i = 1;
	while (env_array[i] != NULL)
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (NULL);
		new->data = ft_strdup(env_array[i]);
		new->unset_flag = 0;
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (first);
}
/*
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
}*/

void	print_toklst(char *header, t_token *tok_first)
{
	dprintf(2, "%s\n", header);
	while (tok_first != NULL)
	{
		printf("type: %i value: %s.\n", tok_first->type, tok_first->value);
		tok_first = tok_first->next;
	}
}

int main(int ac, char **av , char **environment)
{
	char *line;
	t_env *env;
	///char **test;
	//int		exit_code;
	t_token	*tok_first;
	t_tokens tokens;
	t_token *new_tok;
	t_tokens exp_tokens;

	(void)ac;
	(void)av;
	//exit_code = 0;
	print_header();
	env = dup_env(environment);
	//int fdstart[2];
	while (1)
	{
		//dprintf(2, "NEW LOOP\n");
		line = readline("\033[1;33mмини-оболочка-0.1$\033[m ");
		if (!line)
			return(1); // some error ????
		//dprintf(2, "line: %s\n", line);
		//test = ft_split(line, ' ');
		//exec_blt(test, env, exit_code);
		if (ft_strlen(line) != 0)
		{
			tok_first = parser(line);
			//print_toklst("PARSER", tok_first);
			tokens = init_tokens(tok_first);
			new_tok = expander(&tokens);
			//print_toklst("EXPANDER", new_tok);
			exp_tokens = init_exp_tokens(new_tok, env);
			executor(&exp_tokens);
			add_history(line);
		}
		free(line);
	}
	return (0);
}
