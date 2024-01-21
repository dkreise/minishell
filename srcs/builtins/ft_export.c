/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 22:09:13 by rpliego           #+#    #+#             */
/*   Updated: 2024/01/20 19:44:51 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	mod_strcmp(char *cmd, char *env)
{
	int	i;

	i = 0;
	while (cmd[i] && env[i])
	{
		if (cmd[i] == '=' && env[i] == '=')
			return (TRUE);
		if (cmd[i] != env[i])
			return (FALSE);
		i++;
	}
	if (cmd[i] == '\0' && (env[i] == '\0' || env[i] == '='))
		return (TRUE);
	return(FALSE);
}

void	replace_value(char *cmd, t_env *env)
{
	t_env *temp;
	
	temp = env;
	while(temp != NULL)
	{
		if (mod_strcmp(cmd, temp->data) == TRUE)
		{
			// while (*temp->data != '=')
			// 	temp->data++;
			// temp->data++;
			printf("data---->%s\n", temp->data);
			temp->data = ft_strdup(cmd);
			temp->unset_flag = 0;
			printf("data---->%s\n", temp->data);
		}
		temp = temp->next;
	}
}

int	var_exist(char *cmd, t_env *env)
{
	t_env *temp;
	
	temp = env;
	while(temp != NULL)
	{
		if (mod_strcmp(cmd, temp->data) == TRUE)
			return (TRUE);
		temp = temp->next;
	}
	return (FALSE);
}

void	special_export(t_env *env)
{
	int	i;
	int	flag;

	while (env)
	{
		i = 0;
		flag = 0;
		if (env->unset_flag == 0)
		{
			printf("declare -x ");
			while (env->data[i])
			{
				printf("%c", env->data[i]);
				if (env->data[i] == '=')
				{
					flag = 1;
					printf("\"");
				}
				i++;
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
	t_env *new;
	t_env *temp;
	int	i;

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

void	ft_export(char **cmd, t_env **env) // "export" "a=b" "c=g"
{
	int	i;

	i = 1;
	if (!cmd[1])
		special_export(*env);
	else
	{
		while (cmd[i] != NULL)
		{
			if (var_exist(cmd[i], *env) == 1)
			{
				printf("entrooooo\n");
				replace_value(cmd[i], *env);
			}
			else
				normal_export(cmd[i], env);
			//printf("holaa\n\n");
			i++;
		}
	}
}
