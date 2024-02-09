/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:28:18 by rpliego           #+#    #+#             */
/*   Updated: 2024/02/04 16:28:01 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_cnt(t_env *env)
{
	int	cnt;

	cnt = 0;
	while (env)
	{
		if (env->unset_flag == 0)
			cnt ++;
		env = env->next;
	}
	return (cnt);
}

t_env	*our_env(void)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->data = ft_strdup("SHLVL=1");
	env->unset_flag = 0;
	env->next = NULL;
	return (env);
}

char	*update_shlvl(char *str)
{
	int	ato;

	while (*str != '=' && *str)
		str++;
	str++;
	ato = ft_atoi(str);
	ato += 1;
	if (ato > 999 || ato < 0)
	{
		ft_putstr_fd("Reseting SHLVL to 1\n", 2);
		return (ft_strjoin("SHLVL=", "1", 4));
	}
	return (ft_strjoin("SHLVL=", ft_itoa(ato), SECOND));
}

void	*aux_dup_env(char **env_array, t_env *env)
{
	t_env	*new;
	int		i;

	i = 0;
	while (env_array[++i] != NULL)
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (NULL);
		if (ft_strncmp("SHLVL", env_array[i], 5) == 0)
			new->data = update_shlvl(env_array[i]);
		else
			new->data = ft_strdup(env_array[i]);
		new->unset_flag = 0;
		new->next = NULL;
		env->next = new;
		env = new;
	}
	return (NULL);
}

t_env	*dup_env(char **env_array)
{
	t_env	*first;
	t_env	*env;

	first = malloc(sizeof(t_env));
	if (!first)
		return (NULL);
	first->data = ft_strdup(env_array[0]);
	if (ft_strncmp("SHLVL", first->data, 5) == 0)
		first->data = update_shlvl(first->data);
	first->unset_flag = 0;
	first->next = NULL;
	env = first;
	aux_dup_env(env_array, env);
	return (first);
}
