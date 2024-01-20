/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:39:49 by dkreise           #+#    #+#             */
/*   Updated: 2024/01/20 19:42:12 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exp_in_out(t_tokens *tokens, t_token **exp_tok, int *i, int is_pipe)
{
	//char	*val;
	t_token	*tnext;
	int		exp_type;

	tnext = tokens->toks[*i]->next;
	exp_type = tokens->toks[*i]->type + is_pipe;
	if (tnext->type == tokens->toks[*i]->type) // '<<'
	{
		*i = *i + 1;
		exp_type += 2;
		tnext = tnext->next;
	}
	if (tnext->type == SPACE) // '<< ' or '< '
	{
		*i = *i + 1;
		tnext = tnext->next;
	}
	if (tnext->type == NONE) // or <= DOLLAR ???   '<< str' or '< str' or '<<str' or '<str'
	{
		*i = *i + 1;
		//printf("i before exp_str in exp_in: %i\n", *i);
		exp_str(tokens, exp_tok, i, exp_type);
	}
	else
	{
		dprintf(2, "syntax error");
		//exit(258);
	}
}

void	exp_pipe(t_tokens *tokens, t_token **exp_tok, int *i)
{
	t_token	*tnext;

	tnext = tokens->toks[*i]->next;
	if (tnext->type == SPACE)
	{
		*i = *i + 1;
		tnext = tnext->next;
	}
	if (tnext->type == IN || tnext->type == OUT)
	{
		*i = *i + 1;
		exp_in_out(tokens, exp_tok, i, PIPE);
	}
	else if (tnext->type == NONE)
	{
		*i = *i + 1;
		exp_str(tokens, exp_tok, i, PIPE);
	}
}
