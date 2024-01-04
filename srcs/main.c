/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:44:44 by rpliego           #+#    #+#             */
/*   Updated: 2024/01/04 12:10:25 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_header(void)
{
	printf("%s           _       _     _          _ _ %s\n", F, E);
	printf("%s _ __ ___ (_)_ __ (_)___| |__   ___| | |%s\n", F, E);
	printf("%s| '_ ` _ || | '_ || / __| '_ | / _ | | |%s\n", F, E);
	printf("%s| | | | | | | | | | |__ | | | |  __/ | |%s\n", F, E);
	printf("%s|_| |_| |_|_|_| |_|_|___/_| |_||___|_|_|%s\n\n\n", F, E);
}

int main(int ac, char **av , char **env)
{
	char *line;

	(void)ac;
	(void)av;
	int	i;
	int	j;
	i = 0;
	while (env[i] != NULL)
	{
		j = 0;
		while (env[i][j] != '\0')
		{
			printf("%c", env[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	print_header();
	while (1)
	{
		line = readline("\033[1;33mмини-оболочка-0.1$\033[m ");
		printf("%s\n", line);
		add_history(line);
	}
	return (0);
}
