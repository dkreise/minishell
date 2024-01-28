/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:21:27 by rpliego           #+#    #+#             */
/*   Updated: 2024/01/27 13:55:53 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void update_pwd(t_env *env)
{
	t_env *temp;
	char *path_pwd;
	char *path_oldpwd;
	char *aux;

	temp = env;
	while (temp)
	{
		if (mod_strcmp("PWD", temp->data) == TRUE) //|| mod_strcmp("PWD", temp->data) == FALSE) UMMMM NOT SURE
		{
			aux = ft_strdup(temp->data);
			getcwd(path_pwd, sizeof(path_pwd));
			path_pwd = getcwd(NULL, 0);
			temp->data = ft_strjoin("PWD=", path_pwd, 4);
		}
		if (mod_strcmp("OLDPWD", temp->data) == TRUE)
		{
			path_oldpwd = ft_strdup(aux);
			while (*path_oldpwd != '=')
				path_oldpwd++;
			path_oldpwd++;
			temp->data = ft_strjoin("OLDPWD=", path_oldpwd, 4);
		}
		temp = temp->next;
	}
}

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
	int ret;

	ret = 0;
	if (cmd[1] == NULL)
		ret = (cd_no_arg(env));
	else
		ret = (execute_cd(cmd));
	update_pwd(env);
	return (ret);
}