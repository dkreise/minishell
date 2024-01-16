/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:21:27 by rpliego           #+#    #+#             */
/*   Updated: 2024/01/15 18:56:57 by rpliego          ###   ########.fr       */
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
				printf("HOME not set\n");
				return ;
			}
			path_home = ft_strdup(temp->data);
			while (*path_home != '=')
				path_home++;
			path_home++;
			if (access (path_home, F_OK) == -1)
				printf("No such file or directory\n");
			else if (access(path_home, R_OK|W_OK|X_OK) == -1)
				printf("Permission denied\n");
			else
				chdir(path_home);
		}
		temp = temp->next;
	}
}

void	cd_relative(char **cmd)
{
	if (access (cmd[1], F_OK) == -1)
		printf("No such file or directory\n");
	else if (access(cmd[1], R_OK|W_OK|X_OK) == -1)
		printf("Permission denied\n");
	else
		chdir(cmd[1]);
}

void	cd_absolute(char **cmd)
{
	if (access (cmd[1], F_OK) == -1)
		printf("No such file or directory\n");
	else if (access(cmd[1], R_OK|W_OK|X_OK) == -1)
		printf("Permission denied\n");
	else
		chdir(cmd[1]);
}

void	ft_cd(char **cmd, t_env *env)
{
	if (cmd[1] == NULL)
		cd_no_arg(env);
	else if (is_absolute(cmd[1]) == TRUE)
		cd_absolute(cmd);
	else
		cd_relative(cmd);
}
