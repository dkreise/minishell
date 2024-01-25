/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:27:01 by dkreise           #+#    #+#             */
/*   Updated: 2024/01/23 14:43:03 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*find_env(char *str, int *j, t_tokens *tokens)
{
	int		i;
	char	*var;
	char	*val;
	t_env	*temp_env;

	i = 0;
	while ((str[i] == '_' || ft_isalnum(str[i])) && str[i] != '\0')
		i ++;
	*j = i;
	if (i == 0)
	{
		val = ft_strdup("$");
		if (!val)
			malloc_error(NULL, tokens);
		return(val);
	}
	var = ft_substr(str, 0, i);
	if (!var)
	{
		malloc_error(NULL, tokens);
		return (NULL);
	}
	temp_env = tokens->env;
	while(temp_env != NULL)
	{
		if (mod_strcmp(var, temp_env->data) == 1)
			break ;
		temp_env = temp_env->next;
	}
	free(var);
	if (!temp_env)
		return(0);
	i = 0;
	while (temp_env->data[i] != '=')
		i ++;
	val = ft_substr(temp_env->data, i + 1, ft_strlen(temp_env->data) - i - 1);
	if (!val)
	{
		malloc_error(NULL, tokens);
		return (NULL);
	}
	return(val);
}

char	*exp_dollar(t_tokens *tokens, int *i)
{
	t_token	*tnext;
	int		j;
	int		strlen;
	char	*temp_val;
	char	*val;

	tnext = tokens->toks[*i]->next;
	if (!tnext)
	{
		*i = *i + 1;
		val = ft_strdup("$");
		if (!val)
			malloc_error(NULL, tokens);
		return(val);
	}
	j = 0;
	strlen = ft_strlen(tnext->value);
	if (tnext->type == SNGL_Q || tnext->type == DBL_Q)
	{
		*i = *i + 1;
		val = ft_strdup("");
	}
	else if (tnext->type == NONE)
	{
		*i = *i + 2;
		if (tnext->value[0] == '?')
		{
			temp_val = ft_itoa(tokens->prev_exit);
			if (!temp_val)
			{
				malloc_error(NULL, tokens);
				return (NULL);
			}
			j ++;
		}
		else
		{
			temp_val = find_env(tnext->value, &j, tokens);
			if (tokens->error == MALLOC_ERROR)
				return (NULL);
			if (temp_val == 0 && j == strlen)
			{
				val = ft_strdup("");
				if (!val)
				{
					malloc_error(NULL, tokens);
					return (NULL);
				}
				return(val);
			}
		}
		if (j == strlen)
			val = temp_val;
		else //if (j < strlen)
			val = ft_strjoin(temp_val, ft_substr(tnext->value, j, strlen - j), BOTH);
	}
	else
	{
		*i = *i + 1;
		val = ft_strdup("$");
	}
	if (!val)
		malloc_error(NULL, tokens);
	return (val);
}
