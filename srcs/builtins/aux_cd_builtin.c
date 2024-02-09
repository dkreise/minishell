/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_cd_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:45:20 by rpliego           #+#    #+#             */
/*   Updated: 2024/02/09 21:11:25 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_cd(int n)
{
	if (n == 1)
		ft_putstr_fd("HOME not set\n", 2);
	else if (n == 2)
		ft_putstr_fd("No such file or directory\n", 2);
	else if (n == 3)
		ft_putstr_fd("Permission denied\n", 2);
	else if (n == 4)
		ft_putstr_fd("HOME not set\n", 2);
	return (1);
}

void	get_pwd(t_env *env)
{
	t_env	*aux;

	aux = malloc(sizeof(t_env));
	if (!aux)
		return ;
	aux->data = ft_strdup("PWD=");
	aux->next = NULL;
	aux->unset_flag = 0;
	while (env && env->next)
		env = env->next;
	env->next = aux;
}

void	update_pwd(t_env *env, int flag, char *buff)
{
	t_env	*temp;
	char	*path_pwd;
	char	*path_oldpwd;

	temp = env;
	while (temp)
	{
		if (mod_strcmp("PWD", temp->data) == TRUE && temp->unset_flag == 0)
		{
			path_oldpwd = ft_substr(temp->data, 4, ft_strlen(temp->data));
			flag = 1;
			getcwd(buff, sizeof(buff));
			path_pwd = ft_strdup(buff);
			free(temp->data);
			temp->data = ft_strjoin("PWD=", path_pwd, 2);
		}
		if (mod_strcmp("OLDPWD", temp->data) == TRUE && temp->unset_flag == 0)
		{
			free(temp->data);
			temp->data = ft_strjoin("OLDPWD=", path_oldpwd, 0);
		}
		temp = temp->next;
	}
	if (flag == 1)
		free(path_oldpwd);
}
