/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:21:27 by rpliego           #+#    #+#             */
/*   Updated: 2024/01/23 21:56:27 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	cd_no_arg(t_env *env)
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
				return (1);
			}
			path_home = ft_strdup(temp->data);
			while (*path_home != '=')
				path_home++;
			path_home++;
			if (access (path_home, F_OK) == -1)
			{
				printf("No such file or directory\n");
				return (1);
			}
			else if (access(path_home, X_OK) == -1)
			{
				printf("Permission denied\n");
				return (1);
			}
			else
			{
				chdir(path_home);
				return (0);
			}
		}
		if (temp->next == NULL && mod_strcmp("HOME", temp->data) == FALSE)
		{
			printf("HOME not set\n");
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

int	execute_cd(char **cmd)
{
	if (access (cmd[1], F_OK) == -1)
	{
		printf("No such file or directory\n");
		return (1);
	}
	else if (access(cmd[1], X_OK) == -1)
	{
		printf("Permission denied\n");
		return (1);
	}
	else
	{
		chdir(cmd[1]);
		return (0);
	}
}

int	ft_cd(char **cmd, t_env *env)
{
	if (cmd[1] == NULL)
		return(cd_no_arg(env));
	else
		return(execute_cd(cmd));
}
