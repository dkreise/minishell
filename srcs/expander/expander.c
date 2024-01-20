/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:14:15 by dkreise           #+#    #+#             */
/*   Updated: 2024/01/20 20:13:02 by dkreise          ###   ########.fr       */
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

// void	exp_sngl_q(t_tokens *tokens, t_token **exp_tok, int *i)
// {
	
// }

void	exp_spec_char(t_tokens *tokens, t_token **exp_tok, int *i) 
{
	int	tok_type;

	tok_type = tokens->toks[*i]->type;
	if (tok_type == IN || tok_type == OUT)
		exp_in_out(tokens, exp_tok, i, 0);
	else if (tok_type == PIPE)
		exp_pipe(tokens, exp_tok, i);
	else if (tok_type == DOLLAR)
		exp_dollar(tokens, exp_tok, i);
}

t_tokens	init_exp_tokens(t_token *exp_tok, t_env *new_env, int exit_code)
{
	t_tokens	tokens;

	tokens = init_tokens(exp_tok, new_env, exit_code);
	tokens.paths = get_paths(lst_to_arr(tokens.env)); 
	if (!tokens.paths)
		dprintf(2, "paths are null\n");
	// protect get_paths (can return NULL)
	tokens.initfd[0] = dup(STDIN_FILENO);
	tokens.initfd[1] = dup(STDOUT_FILENO);
	tokens.cmd_cnt = 0;
	return (tokens);
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
