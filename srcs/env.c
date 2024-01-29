/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:28:18 by rpliego           #+#    #+#             */
/*   Updated: 2024/01/29 18:35:29 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (ft_strjoin("SHLVL=", ft_itoa(ato), 4));
}

t_env	*dup_env(char **env_array)
{
	t_env	*first;
	t_env	*env;
	t_env	*new;
	int		i;

	if (!env_array)
		return (NULL);
	first = malloc(sizeof(t_env));
	if (!first)
		return (NULL);
	first->data = ft_strdup(env_array[0]);
	if (ft_strncmp("SHLVL", first->data, 5) == 0)
		first->data = ft_strdup(update_shlvl(env_array[0]));
	first->unset_flag = 0;
	first->next = NULL;
	env = first;
	i = 0;
	while (env_array[++i] != NULL)
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (NULL);
		if (ft_strncmp("SHLVL", env_array[i], 5) == 0)
			new->data = ft_strdup(update_shlvl(env_array[i]));
		else
			new->data = ft_strdup(env_array[i]);
		new->unset_flag = 0;
		new->next = NULL;
		env->next = new;
		env = new;
	}
	return (first);
}
