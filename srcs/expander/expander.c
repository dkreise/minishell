/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:14:15 by dkreise           #+#    #+#             */
/*   Updated: 2024/02/04 15:54:38 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exp_spec_char(t_tokens *tokens, t_token **exp_tok, int *i)
{
	int	tok_type;

	tok_type = tokens->toks[*i]->type;
	if (tok_type == IN || tok_type == OUT)
		exp_in_out(tokens, exp_tok, i, 0);
	else if (tok_type == PIPE)
		exp_pipe(tokens, exp_tok, i);
	else if (tok_type == DOLLAR)
		exp_str(tokens, exp_tok, i, NONE);
}

t_tokens	init_exp_tokens(t_token **exp_tok, t_env *new_env, int exit_code)
{
	t_tokens	tokens;
	char		**env_lst;

	tokens = init_tokens(exp_tok, new_env, exit_code);
	if ((*exp_tok)->error == MALLOC_ERROR)
		return (tokens);
	env_lst = lst_to_arr(exp_tok, tokens.env);
	if ((*exp_tok)->error == MALLOC_ERROR)
		return (tokens);
	tokens.paths = get_paths(exp_tok, env_lst, 0, 0);
	if ((*exp_tok)->error == MALLOC_ERROR)
	{
		free(env_lst);
		return (tokens);
	}
	tokens.initfd[0] = dup(STDIN_FILENO);
	tokens.initfd[1] = dup(STDOUT_FILENO);
	tokens.cmd_cnt = 0;
	tokens.error = 0;
	free_lst(env_lst);
	return (tokens);
}

t_token	*expander(t_tokens *tokens)
{
	int		i;
	t_token	*exp_tok;

	exp_tok = NULL;
	i = 0;
	while (i < tokens->tok_cnt)
	{
		if (tokens->toks[i]->type == NONE)
			exp_str(tokens, &exp_tok, &i, NONE);
		else if (tokens->toks[i]->type == SPACET)
			i ++;
		else if (tokens->toks[i]->type == SNGL_Q)
			exp_str(tokens, &exp_tok, &i, NONE);
		else if (tokens->toks[i]->type == DBL_Q)
			exp_str(tokens, &exp_tok, &i, NONE);
		else if (tokens->toks[i]->type >= DOLLAR)
			exp_spec_char(tokens, &exp_tok, &i);
		if (tokens->error != 0)
			break ;
	}
	return (exp_tok);
}
