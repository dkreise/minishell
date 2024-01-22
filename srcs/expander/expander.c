/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:14:15 by dkreise           #+#    #+#             */
/*   Updated: 2024/01/22 16:44:01 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*exp_dbl_q(t_tokens *tokens, int *i)
{
	//char		*line;
	t_token		*first_dbl_tok;
	t_tokens	dbl_tokens;
	char		*temp_val;
	char		*val;
	int			j;

	first_dbl_tok = parser(tokens->toks[*i]->value);
	//print_toklst("DBL QUOTES PARSER", first_dbl_tok);
	dbl_tokens = init_tokens(first_dbl_tok, tokens->env, tokens->prev_exit);
	j = 0;
	val = ft_strdup("");
	temp_val = NULL;
	while (j < dbl_tokens.tok_cnt)
	{
		if (dbl_tokens.toks[j]->type == DOLLAR)
			temp_val = exp_dollar(&dbl_tokens, &j);
		else
		{
			temp_val = ft_strdup(dbl_tokens.toks[j]->value);
			// malloc protection
			j ++;
		}
		val = ft_strjoin(val, temp_val, BOTH);
		// malloc protection
	}
	//free dbl_tokens
	*i = *i + 1;
	return(val);
}

void	exp_str(t_tokens *tokens, t_token **exp_tok, int *i, int exp_type)
{
	char	*temp_val;
	char	*val;
	t_token	*tcur;

	tcur = tokens->toks[*i];
	val = ft_strdup("");
	temp_val = NULL;
	while (tcur->type <= DOLLAR && tcur->type != SPACE)
	{
		if (tcur->type == NONE)// || tcur->type == SNGL_Q)
		{
			temp_val = ft_strdup(tcur->value);
			// malloc protection
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
			// malloc protection
			*i = *i + 1;
		}
		else if (tcur->type == DBL_Q)
			temp_val = exp_dbl_q(tokens, i);
		else if (tcur->type == DOLLAR)
			temp_val = exp_dollar(tokens, i);
		val = ft_strjoin(val, temp_val, BOTH);
		// malloc protection
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

t_tokens	init_exp_tokens(t_token *exp_tok, t_env *new_env, int exit_code)
{
	t_tokens	tokens;

	tokens = init_tokens(exp_tok, new_env, exit_code); //protect it
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
	//printf("tok cnt: %i\n", tokens->tok_cnt);
	while (i < tokens->tok_cnt)
	{
		//printf("i in loop: %i\n", i);
		if (tokens->toks[i]->type == NONE)
			exp_str(tokens, &exp_tok, &i, NONE);
		else if (tokens->toks[i]->type == SPACE)
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
