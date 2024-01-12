/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:21:27 by rpliego           #+#    #+#             */
/*   Updated: 2024/01/12 17:15:25 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_absolute(char *str)
{
	if (str[0] == '/')
		return (TRUE);
	return (FALSE);
}

void	cd_no_arg(t_env *env)
{
	t_env *temp;
	char *path_home;

	temp = env;
	while (temp)
	{
		if (mod_strcmp("HOME", temp->data) == TRUE)
		{
			if (temp->unset_flag == 1)
			{
				printf("мини-оболочка: cd: HOME not set\n");
				return ;
			}
			path_home = ft_strdup(temp->data);
			while (*path_home != '=')
				path_home++;
			path_home++;
			chdir(path_home);
		}
		temp = temp->next;
	}
}

void	cd_relative(char **cmd)
{
	
}

void	ft_cd(char **cmd, t_env *env)
{
	if (cmd[1] == NULL)
	{
		cd_no_arg(env);
		return ;
	}
	if (is_absolute(cmd[1]) == TRUE)
		chdir(cmd[1]);
	else
		cd_relative(cmd);
}