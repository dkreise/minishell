/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:14:15 by dkreise           #+#    #+#             */
/*   Updated: 2024/01/16 13:33:19 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exp_str(t_tokens *tokens, t_token **exp_tok, int *i, int exp_type)
{
	char	*val;
	//t_token	*tnext;
	int		next_type;

	//tnext = tokens->toks[*i]->next
	val = NULL;
	//printf("i in exp_str: %i\n", *i);
	if (tokens->toks[*i]->next)
		next_type = tokens->toks[*i]->next->type;
	else
		next_type = SPACE;
	if (next_type == SPACE || next_type == IN || next_type == OUT || next_type == PIPE)
	{
		val = ft_strdup(tokens->toks[*i]->value);
		//malloc protection
		*i = *i + 1;
	}
	// else if SNGL_Q or DBL_Q   -->  exp_quotes
	// else if DOLLAR  --> exp_dollar
	addback_token(exp_tok, val, exp_type);
}

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
		exit(258);
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

void	exp_spec_char(t_tokens *tokens, t_token **exp_tok, int *i) 
{
	int	tok_type;

	tok_type = tokens->toks[*i]->type;
	if (tok_type == IN || tok_type == OUT)
		exp_in_out(tokens, exp_tok, i, 0);
	else if (tok_type == PIPE)
		exp_pipe(tokens, exp_tok, i);
	// else if (tok_type == DOLLAR)
}

t_token	*expander(t_tokens *tokens)
{
	int		i;
	t_token *exp_tok;

	exp_tok = NULL;
	i = 0;
	//printf("tok cnt: %i\n", tokens->tok_cnt);
	while (i < tokens->tok_cnt)
	{
		//printf("i in loop: %i\n", i);
		if (tokens->toks[i]->type == NONE)
			exp_str(tokens, &exp_tok, &i, NONE);
		else if (tokens->toks[i]->type == SPACE)
			i ++;
		//else if (tokens->toks[i]->type == SNGL_Q)
		//	...
		//else if (tokens->toks[i]->type == DBL_Q)
		//	...
		else if (tokens->toks[i]->type >= DOLLAR)
			exp_spec_char(tokens, &exp_tok, &i);
	}
	return (exp_tok);
}
