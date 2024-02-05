/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 20:09:16 by dkreise           #+#    #+#             */
/*   Updated: 2024/01/27 13:46:03 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*exp_none_or_snglq(t_token *tcur, int *i, t_tokens *tokens)
{
	char	*temp_val;

	temp_val = NULL;
	if (tcur->type == NONE)
	{
		temp_val = ft_strdup(tcur->value);
		if (temp_val == NULL)
		{
			malloc_error(NULL, tokens);
			return (NULL);
		}
		*i = *i + 1;
	}
	else if (tcur->type == SNGL_Q)
	{
		temp_val = ft_substr(tcur->value, 1, ft_strlen(tcur->value) - 2);
		if (temp_val == NULL)
		{
			malloc_error(NULL, tokens);
			return (NULL);
		}
		*i = *i + 1;
	}
	return (temp_val);
}

static char	*exp_tok_str(t_token *tcur, t_tokens *tokens, int *i, char *val)
{
	char	*temp_val;

	temp_val = NULL;
	if (tcur->type == NONE || tcur->type == SNGL_Q)
		temp_val = exp_none_or_snglq(tcur, i, tokens);
	else if (tcur->type == DBL_Q)
		temp_val = exp_dbl_q(tokens, i);
	else if (tcur->type == DOLLAR)
		temp_val = exp_dollar(tokens, i);
	if (temp_val == NULL || tokens->error == MALLOC_ERROR)
		return (NULL);
	val = ft_strjoin(val, temp_val, BOTH);
	if (val == NULL)
	{
		malloc_error(NULL, tokens);
		return (NULL);
	}
	return (val);
}

void	exp_str(t_tokens *tokens, t_token **exp_tok, int *i, int exp_type)
{
	char	*val;
	t_token	*tcur;

	if (tokens->error == MALLOC_ERROR)
		return ;
	tcur = tokens->toks[*i];
	val = ft_strdup("");
	if (!val)
	{
		malloc_error(NULL, tokens);
		return ;
	}
	while (tcur->type <= DOLLAR && tcur->type != SPACET)
	{
		val = exp_tok_str(tcur, tokens, i, val);
		if (val == NULL)
			return ;
		if (*i >= tokens->tok_cnt)
			break ;
		tcur = tokens->toks[*i];
		if (!tcur)
			break ;
	}
	addback_token(exp_tok, val, exp_type);
}
