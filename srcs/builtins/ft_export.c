/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 22:09:13 by rpliego           #+#    #+#             */
/*   Updated: 2024/01/09 21:24:07 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_exist(char **line, t_env *env)
{
	int	i; 
	t_env *temp;

	i = 0;
	temp = env;
	while(temp != NULL)
	{
		if (strcmp(line[1], temp->data) == 0)
			return (1);
		temp = temp->next;
	}
	return (0);
}

void	special_export(t_env *env)
{
	int	i;
	int	flag;

	while (env)
	{
		i = 0;
		flag = 0;
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
		env = env->next;
	}
	
}

void	normal_export(char **line, t_env **env)
{
	t_env *new;
	t_env *temp;
	int	i;

	i = 1;
	temp = *env;
	while (line[i])
	{
		new = malloc(sizeof(t_env));
		new->data = ft_strdup(line[i]);
		new->next = NULL;
		if (temp == NULL)
			*env = new;
		else
		{
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = new;
		}
		i++;
	}
}

void	ft_export(char **line, t_env **env) // "export" "a=b"
{
	if (!line[1])
		special_export(*env);
	else
	{
		if (check_exist(line, *env) == 0)
			normal_export(line, env);
	}
}
