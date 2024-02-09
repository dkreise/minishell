/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:21:27 by rpliego           #+#    #+#             */
/*   Updated: 2024/02/09 00:47:26 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	cd_no_arg(t_env *env)
{
	t_env	*temp;
	char	*path_home;

	temp = env;
	while (temp)
	{
		if (mod_strcmp("HOME", temp->data) == TRUE)
		{
			if (temp->unset_flag == 1)
				return (error_cd(1));
			path_home = ft_substr(temp->data, 5, ft_strlen(temp->data));
			if (access (path_home, F_OK) == -1)
				return (free(path_home), error_cd(2));
			else if (access(path_home, X_OK) == -1)
				return (free(path_home), error_cd(3));
			else
			{
				chdir(path_home);
				free(path_home);
			}
			return (0);
		}
		temp = temp->next;
	}
	return (error_cd(1));
}

int	execute_cd(char **cmd)
{
	char	*test;

	if (access (cmd[1], F_OK) == -1)
	{
		ft_putstr_fd("No such file or directory\n", 2);
		return (1);
	}
	else if (access(cmd[1], X_OK) == -1)
	{
		ft_putstr_fd("Permission denied\n", 2);
		return (1);
	}
	else
	{
		test = strdup(cmd[1]);
		chdir(test);
		free(test);
		return (0);
	}
}

int	ft_cd(char **cmd, t_env *env)
{
	t_env	*aux;
	int		ret;
	int		flag;

	aux = env;
	ret = 0;
	flag = 0;
	while (aux)
	{
		if (mod_strcmp("PWD", aux->data) == TRUE)
			flag = 1;
		aux = aux->next;
	}
	if (flag == 0)
		get_pwd(env);
	if (cmd[1] == NULL)
		ret = (cd_no_arg(env));
	else
		ret = (execute_cd(cmd));
	update_pwd(env);
	return (ret);
}
