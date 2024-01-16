/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:57:38 by rpliego           #+#    #+#             */
/*   Updated: 2024/01/15 18:03:52 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_exit(char **cmd, t_env *env, int exit_code)//NOT OK
{
	t_env *aux;

	aux = env;
	if (cmd[1][0] == '$')
	{
		printf("exit\n");
		exit_code = ft_atoi(aux->data);
		printf("exit code ------->%i\n", exit_code);
	}
	printf("HOLAAAA\n");
}