/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:14:15 by dkreise           #+#    #+#             */
/*   Updated: 2024/01/26 14:41:17 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exp_str(t_tokens *tokens, t_token **exp_tok, int *i, int exp_type)
{
	char	*temp_val;
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
	temp_val = NULL;
	while (tcur->type <= DOLLAR && tcur->type != SPACET)
	{
		if (tcur->type == NONE)
		{
			temp_val = ft_strdup(tcur->value);
			if (!temp_val)
			{
				malloc_error(NULL, tokens);
				return ;
			}
			*i = *i + 1;
		}
		else if (tcur->type == SNGL_Q)
		{
			temp_val = ft_substr(tcur->value, 1, ft_strlen(tcur->value) - 2);
			if (!temp_val)
			{
				malloc_error(NULL, tokens);
				return ;
			}
			*i = *i + 1;
		}
		else if (tcur->type == DBL_Q)
			temp_val = exp_dbl_q(tokens, i);
		else if (tcur->type == DOLLAR)
			temp_val = exp_dollar(tokens, i);
		if (tokens->error == MALLOC_ERROR)
			return ;
		val = ft_strjoin(val, temp_val, BOTH);
		if (!val)
		{
			malloc_error(NULL, tokens);
			return ;
		}
		if (*i >= tokens->tok_cnt)
			break ;
		tcur = tokens->toks[*i];
		if (!tcur)
			break ;
	}
	addback_token(exp_tok, val, exp_type);
}

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

	tokens = init_tokens(exp_tok, new_env, exit_code); //protect it
	if ((*exp_tok)->error == MALLOC_ERROR)
		return (tokens);
	tokens.paths = get_paths(lst_to_arr(tokens.env)); //how to free lst??
	if (!tokens.paths)
		dprintf(2, "paths are null\n");
	// protect get_paths (can return NULL)
	tokens.initfd[0] = dup(STDIN_FILENO);
	tokens.initfd[1] = dup(STDOUT_FILENO);
	tokens.cmd_cnt = 0;
	tokens.error = 0;
	return (tokens);
}

t_token	*expander(t_tokens *tokens)
{
	int		i;
	t_token *exp_tok;

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
