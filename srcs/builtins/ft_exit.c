/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:57:38 by rpliego           #+#    #+#             */
/*   Updated: 2024/01/18 11:50:28 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_exit(char **cmd, t_env *env, int exit_code)
{
	// t_env *aux;

	// aux = env;
	if (cmd[1][0] == '$' && mod_strcmp(cmd[1] + 1, env->data) == 0)
	{
		printf("exit\n");
		exit_code = ft_atoi(env->data);
		printf("exit code -------> %i\n", exit_code);
	}
	printf("HOLAAAA\n");
}