/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:39:49 by dkreise           #+#    #+#             */
/*   Updated: 2024/01/29 18:21:17 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exp_in_out(t_tokens *tokens, t_token **exp_tok, int *i, int ispipe)
{
	t_token	*tnext;
	int		exp_type;

	tnext = tokens->toks[*i]->next;
	exp_type = tokens->toks[*i]->type + ispipe;
	if (tnext->type == tokens->toks[*i]->type) // '<<'
	{
		*i = *i + 1;
		exp_type += 2;
		tnext = tnext->next;
	}
	if (tnext->type == SPACET) // '<< ' or '< '
	{
		*i = *i + 1;
		tnext = tnext->next;
	}
	if (tnext->type <= DOLLAR)
	{
		*i = *i + 1;
		exp_str(tokens, exp_tok, i, exp_type);
	}
	else if (tnext->type == PIPE)
	{
		*i = *i + 1;
		tnext = tnext->next;
		if (tnext->type == SPACET)
		{
			*i = *i + 1;
			tnext = tnext->next;
		}
		if (tnext->type <= DOLLAR) // or <= DOLLAR ???   '<< str' or '< str' or '<<str' or '<str'
		{
			*i = *i + 1;
			exp_str(tokens, exp_tok, i, exp_type);
		}
		else
		{
			*i = *i + 1;
			tokens->error = tnext->type;
		}
	}
	else
	{
		*i = *i + 1;
		tokens->error = tnext->type;
	}
}

void	exp_pipe(t_tokens *tokens, t_token **exp_tok, int *i)
{
	t_token	*tnext;

	tnext = tokens->toks[*i]->next;
	if (tnext->type == SPACET)
	{
		*i = *i + 1;
		tnext = tnext->next;
	}
	if (tnext->type == IN || tnext->type == OUT)
	{
		*i = *i + 1;
		exp_in_out(tokens, exp_tok, i, PIPE);
	}
	else if (tnext->type <= DOLLAR )
	{
		*i = *i + 1;
		exp_str(tokens, exp_tok, i, PIPE);
	}
	else
	{
		*i = *i + 1;
		tokens->error = PIPE;
	}
}
