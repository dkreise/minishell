/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:39:49 by dkreise           #+#    #+#             */
/*   Updated: 2024/02/03 15:41:30 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*exp_in_out_aux(t_token *tnext, t_tokens *tokens, int *i, int *exp_type)
{
	if (tnext->type == tokens->toks[*i]->type)
	{
		*i = *i + 1;
		*exp_type = *exp_type + 2;
		tnext = tnext->next;
	}
	if (tnext->type == SPACET)
	{
		*i = *i + 1;
		tnext = tnext->next;
	}
	*i = *i + 1;
	return (tnext);
}

void	exp_in_out(t_tokens *tokens, t_token **exp_tok, int *i, int is_pipe)
{
	t_token	*tnext;
	int		exp_type;

	tnext = tokens->toks[*i]->next;
	exp_type = tokens->toks[*i]->type + is_pipe;
	tnext = exp_in_out_aux(tnext, tokens, i, &exp_type);
	if (tnext->type <= DOLLAR)
		exp_str(tokens, exp_tok, i, exp_type);
	else
		tokens->error = tnext->type;
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
	*i = *i + 1;
	if (tnext->type == IN || tnext->type == OUT)
		exp_in_out(tokens, exp_tok, i, PIPE);
	else if (tnext->type <= DOLLAR)
		exp_str(tokens, exp_tok, i, PIPE);
	else
		tokens->error = PIPE;
}
