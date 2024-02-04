/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:44:44 by rpliego           #+#    #+#             */
/*   Updated: 2024/02/04 16:10:55 by dkreise          ###   ########.fr       */
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

void	print_toklst(char *header, t_token *tok_first)
{
	dprintf(2, "%s\n", header);
	while (tok_first != NULL)
	{
		printf("type: %i value: %s.\n", tok_first->type, tok_first->value);
		tok_first = tok_first->next;
	}
}

void update_global(int *err_exit)
{
	if (g_exit > 0)
	{
		g_exit = 0;
		err_exit[0] = 1;
	}
}

int	main(int ac, char **av, char **environment)
{
	char	*line;
	t_env	*env;

	(void)av;
	line = NULL;
	if (ac > 1)
	{
		ft_putstr_fd("ONLY ./minishell\n", 2);
		return (1);
	}
	print_header();
	if (*environment == NULL)
		env = our_env();
	else
		env = dup_env(environment);
	g_exit = 0;
	mini_loop(line, env);
	return (0);
}
