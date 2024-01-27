/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_dbl_q.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:40:36 by dkreise           #+#    #+#             */
/*   Updated: 2024/01/27 13:43:00 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*dblq_malloc_err(t_tokens dbl_tokens, t_tokens *tokens)
{
	malloc_error(NULL, tokens);
	free_tokens(&dbl_tokens, PARS);
	return (NULL);
}

char	*exp_tok_dblq(t_tokens dbl_tokens, t_tokens *tokens, int *j)
{
	char	*temp_val;

	if (dbl_tokens.toks[*j]->type == DOLLAR)
	{
		temp_val = exp_dollar(&dbl_tokens, j);
		if (dbl_tokens.error == MALLOC_ERROR)
		{
			tokens->error = MALLOC_ERROR;
			free_tokens(&dbl_tokens, PARS);
			return (NULL);
		}
	}
	else
	{
		temp_val = ft_strdup(dbl_tokens.toks[*j]->value);
		if (!temp_val)
			return (dblq_malloc_err(dbl_tokens, tokens));
		*j = *j + 1;
	}
	return (temp_val);
}

char	*exp_dblq_aux(t_tokens dbl_tokens, t_tokens *tokens)
{
	int		j;
	char	*temp_val;
	char	*val;

	j = 0;
	val = ft_strdup("");
	if (!val)
		return (dblq_malloc_err(dbl_tokens, tokens));
	temp_val = NULL;
	while (j < dbl_tokens.tok_cnt)
	{
		temp_val = exp_tok_dblq(dbl_tokens, tokens, &j);
		if (!temp_val)
			return (NULL);
		val = ft_strjoin(val, temp_val, BOTH);
		if (!val)
			return (dblq_malloc_err(dbl_tokens, tokens));
	}
	return (val);
}

char	*exp_dbl_q(t_tokens *tokens, int *i)
{
	t_token		*first_dbl_tok;
	t_tokens	dbl_tokens;
	char		*val;

	first_dbl_tok = parser(tokens->toks[*i]->value);
	if (first_dbl_tok && first_dbl_tok->error == MALLOC_ERROR)
	{
		tokens->error = MALLOC_ERROR;
		free_tok(&first_dbl_tok);
		return (NULL);
	}
	dbl_tokens = init_tokens(&first_dbl_tok, tokens->env, tokens->prev_exit);
	if (first_dbl_tok && first_dbl_tok->error == MALLOC_ERROR)
	{
		tokens->error = MALLOC_ERROR;
		free_tok(&first_dbl_tok);
		return (NULL);
	}
	val = exp_dblq_aux(dbl_tokens, tokens);
	*i = *i + 1;
	free_tokens(&dbl_tokens, PARS);
	return (val);
}
