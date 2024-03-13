/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 22:09:13 by rpliego           #+#    #+#             */
/*   Updated: 2024/03/13 13:12:16 by dkreise          ###   ########.fr       */
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
			free(temp->data);
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

// int	have_numb(char **cmd)
// {
// 	int	i;

// 	i = 0;
// 	while (cmd[i])
// 	{
// 		if (ft_isdigit(cmd[i][0]) == TRUE
// 			|| cmd[i][0] == '/' || cmd[i][0] == '=')
// 		{
// 			ft_putstr_fd("export: '", 2);
// 			ft_putstr_fd(cmd[i], 2);
// 			ft_putstr_fd("': not a valid identifier\n", 2);
// 			return (TRUE);
// 		}
// 		i++;
// 	}
// 	return (FALSE);
// }

int	have_numb(char *cmd)
{
	//int	i;
	int	j;
	int	exit_code;

	//i = 0;
	exit_code = 0;
	//while (cmd[i])
	//{
		j = 0;
		while ((cmd[j] == '_' || ft_isalnum(cmd[j])) && cmd[j] != '\0')
			j ++;
		if (ft_isdigit(cmd[0]) || cmd[0] == '='
			|| (cmd[j] != '=' && cmd[j] != '\0'))
		{
			ft_putstr_fd("export: '", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			exit_code = 1;
		}
		//i++;
	//}
	return (exit_code);
}

// int	ft_export(char **cmd, t_env **env)
// {
// 	int	i;
// 	int numb;

// 	i = 1;
// 	if (!cmd[1])
// 		special_export(*env);
// 	else
// 	{
// 		numb = have_numb(cmd);
// 		if (numb == FALSE)
// 		{
// 			while (cmd[i] != NULL)
// 			{
// 				if (var_exist(cmd[i], *env) == 1)
// 					replace_value(cmd[i], *env);
// 				else
// 					normal_export(cmd[i], env);
// 				i++;
// 			}
// 		}
// 		else
// 			return (1);
// 	}
// 	return (0);
// }

int	ft_export(char **cmd, t_env **env)
{
	int	i;
	int exit_code;

	i = 1;
	exit_code = 0;
	if (!cmd[1])
		special_export(*env);
	else
	{
		while (cmd[i] != NULL)
		{
			if (have_numb(cmd[i]) == 0)
			{
				if (var_exist(cmd[i], *env) == 1)
					replace_value(cmd[i], *env);
				else
					normal_export(cmd[i], env);
			}
			else
				exit_code = 1;
			i++;
		}
	}
	return (exit_code);
}
