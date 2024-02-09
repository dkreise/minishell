/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_dollar_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:44:07 by dkreise           #+#    #+#             */
/*   Updated: 2024/02/08 15:07:08 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_env	*find_var(t_tokens *tokens, char *var)
{
	t_env	*temp_env;

	temp_env = tokens->env;
	while (temp_env != NULL)
	{
		if (mod_strcmp(var, temp_env->data) == 1 && temp_env->unset_flag == 0)
			break ;
		temp_env = temp_env->next;
	}
	free(var);
	return (temp_env);
}

static char	*just_dollar(t_tokens *tokens)
{
	char	*val;

	val = ft_strdup("$");
	if (!val)
		malloc_error(NULL, tokens);
	return (val);
}

char	*find_env(char *str, size_t *j, t_tokens *tokens)
{
	size_t	i;
	char	*var;
	char	*val;
	t_env	*temp_env;

	i = 0;
	while ((str[i] == '_' || ft_isalnum(str[i])) && str[i] != '\0')
		i ++;
	*j = i;
	if (i == 0)
		return (just_dollar(tokens));
	var = ft_substr(str, 0, i);
	if (!var)
		return (dol_malloc_err(tokens));
	temp_env = find_var(tokens, var);
	if (!temp_env)
		return (0);
	i = 0;
	while (temp_env->data[i] != '=')
		i ++;
	val = ft_substr(temp_env->data, i + 1, ft_strlen(temp_env->data) - i - 1);
	if (!val)
		return (dol_malloc_err(tokens));
	return (val);
}
