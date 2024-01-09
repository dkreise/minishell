/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 22:09:13 by rpliego           #+#    #+#             */
/*   Updated: 2024/01/09 18:51:22 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	special_export(t_env *env)
{
	int	i;
	int	flag;

	flag = 0;
	while (env)
	{
		i = 0;
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
		{
			printf("\"");
			flag = 0;
		}
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
		normal_export(line, env);
	ft_env(*env);
}
