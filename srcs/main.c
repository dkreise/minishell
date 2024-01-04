/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:44:44 by rpliego           #+#    #+#             */
/*   Updated: 2024/01/04 16:55:43 by rpliego          ###   ########.fr       */
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

void	ft_export(char *line, t_env **env)
{
	t_env *new;
	int	i;

	i = 0;
	new = malloc(sizeof(t_env));
	while (*line != ' ')
		line++;
	line++;
	new->data = ft_strdup(line);
	new->next = NULL;
	if (*env == NULL) {
        *env = new;
	}
	// while (*line != '\0')
	// {
	// }	
}

void	check_cmd(char *line, t_env *env)
{
		if (ft_strncmp(line, "env", 3) == 0)
		{
			while (env)
			{
				printf("%s\n", env->data);
				env = env->next;
			}
		}
		if (ft_strncmp(line, "export", 6) == 0)
		{
			ft_export(line, &env);
		}
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
	first->next = NULL;
	env = first;
	i = 1;
	while (env_array[i] != NULL)
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (NULL);
		new->data = ft_strdup(env_array[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (first);
}

int main(int ac, char **av , char **enviroment)
{
	char *line;
	t_env *env;

	(void)ac;
	(void)av;
	print_header();
	env = dup_env(enviroment);
	while (1)
	{
		line = readline("\033[1;33mмини-оболочка-0.1$\033[m ");
		check_cmd(line, env);
		//printf("%s\n", line);
		add_history(line);
	}
	return (0);
}
