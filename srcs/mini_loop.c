/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:39:15 by rpliego           #+#    #+#             */
/*   Updated: 2024/01/29 18:35:27 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_loop(char *line, t_env *env, int err_exit[2])
{
	while (1)
	{
		do_signals(INTERACTIVE);
		do_sigign(SIGQUIT);
		line = readline("\033[1;33mмини-оболочка-0.1$\033[m ");
		do_sigign(SIGINT);
		if (!line)
		{
			if (isatty(STDIN_FILENO))
				write(2, "exit\n", 6);
			free_env(&env);
			exit(0);
		}
		if (ft_strlen(line) != 0)
		{
			err_exit[1] = new_exit(line, env, err_exit[0]);
			add_history(line);
			err_exit[0] = err_exit[1];
		}
		g_exit = 0;
		free(line);
	}
}
