/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 22:09:13 by rpliego           #+#    #+#             */
/*   Updated: 2024/01/29 18:26:00 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	replace_value(char *cmd, t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp != NULL)
	{
		if (mod_strcmp(cmd, temp->data) == TRUE)
		{
			temp->data = ft_strdup(cmd);
			temp->unset_flag = 0;
		}
		temp = temp->next;
	}
}

void	special_export(t_env *env)
{
	int	i;
	int	flag;

	while (env)
	{
		i = -1;
		flag = 0;
		if (env->unset_flag == 0)
		{
			printf("declare -x ");
			while (env->data[++i])
			{
				printf("%c", env->data[i]);
				if (env->data[i] == '=')
				{
					flag = 1;
					printf("\"");
				}
			}
			if (flag == 1)
				printf("\"");
			printf("\n");
		}
		env = env->next;
	}
}

void	normal_export(char *cmd, t_env **env)
{
	t_env	*new;
	t_env	*temp;
	int		i;

	i = 1;
	temp = *env;
	new = malloc(sizeof(t_env));
	new->data = ft_strdup(cmd);
	new->unset_flag = 0;
	new->next = NULL;
	if (temp == NULL)
		*env = new;
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

int	have_numb(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (ft_isdigit(cmd[i][0]) == TRUE)
		{
			printf("export: '%s': not a valid identifier\n", cmd[i]);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

void	ft_export(char **cmd, t_env **env)
{
	int	i;

	i = 1;
	if (!cmd[1])
		special_export(*env);
	else if (have_numb(cmd) == FALSE)
	{
		while (cmd[i] != NULL)
		{
			if (var_exist(cmd[i], *env) == 1)
				replace_value(cmd[i], *env);
			else
				normal_export(cmd[i], env);
			i++;
		}
	}
}
