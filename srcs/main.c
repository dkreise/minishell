/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:44:44 by rpliego           #+#    #+#             */
/*   Updated: 2024/02/07 14:15:30 by rpliego          ###   ########.fr       */
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
