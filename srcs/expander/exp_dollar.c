/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:27:01 by dkreise           #+#    #+#             */
/*   Updated: 2024/02/04 11:25:05 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*dol_malloc_err(t_tokens *tokens)
{
	malloc_error(NULL, tokens);
	return (NULL);
}

static char	*exp_tok_dol_aux(t_tokens *tokens)
{
	char	*val;

	val = ft_strdup("");
	if (val == NULL)
		return (dol_malloc_err(tokens));
	return (val);
}

static char	*exp_exit(t_tokens *tokens)
{
	if (g_exit != 0)
		return (ft_itoa(g_exit));
	else
		return (ft_itoa(tokens->prev_exit));
}

static char	*exp_tok_dol(t_token *tnext, t_tokens *tokens)
{
	char	*temp_val;
	size_t	j;

	j = 0;
	if (tnext->value[0] == '?')
	{
		temp_val = exp_exit(tokens);
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
	else
		return (ft_strjoin(temp_val,
				ft_substr(tnext->value, j, ft_strlen(tnext->value) - j), BOTH));
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
		return (val);
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
