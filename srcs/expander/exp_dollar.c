/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:27:01 by dkreise           #+#    #+#             */
/*   Updated: 2024/01/26 16:27:19 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*dol_malloc_err(t_tokens *tokens)
{
	malloc_error(NULL, tokens);
	return (NULL);
}

char	*exp_tok_dol_aux(t_tokens *tokens)
{
	char	*val;

	val = ft_strdup("");
	if (val == NULL)
		return (dol_malloc_err(tokens));
	return(val);
}

char	*exp_tok_dol(t_token *tnext, t_tokens *tokens)
{
	char	*temp_val;
	size_t	j;

	j = 0;
	if (tnext->value[0] == '?')
	{
		temp_val = ft_itoa(tokens->prev_exit);
		if (!temp_val)
			return (dol_malloc_err(tokens));
		j ++;
	}
	else
	{
		temp_val = find_env(tnext->value, &j, tokens);
		if (tokens->error == MALLOC_ERROR)
			return (NULL);
		if (temp_val == 0 && j == ft_strlen(tnext->value))
			return (exp_tok_dol_aux(tokens));
	}
	if (j == ft_strlen(tnext->value))
		return (temp_val);
	else //if (j < strlen)
		return (ft_strjoin(temp_val, ft_substr(tnext->value, j, ft_strlen(tnext->value) - j), BOTH));
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
	{
		val = ft_strdup("$");
		if (!val)
			malloc_error(NULL, tokens);
		return(val);
	}
	var = ft_substr(str, 0, i);
	if (!var)
		return (dol_malloc_err(tokens));
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
		return (dol_malloc_err(tokens));
	return(val);
}

char	*exp_dollar(t_tokens *tokens, int *i)
{
	t_token	*tnext;
	char	*val;

	tnext = tokens->toks[*i]->next;
	*i = *i + 1;
	if (!tnext)
	{
		val = ft_strdup("$");
		if (!val)
			malloc_error(NULL, tokens);
		return(val);
	}
	if (tnext->type == SNGL_Q || tnext->type == DBL_Q)
		val = ft_strdup("");
	else if (tnext->type == NONE)
	{
		*i = *i + 1;
		val = exp_tok_dol(tnext, tokens);
	}
	else
		val = ft_strdup("$");
	if (!val)
		malloc_error(NULL, tokens);
	return (val);
}
