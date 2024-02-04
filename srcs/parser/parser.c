/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:09:32 by dkreise           #+#    #+#             */
/*   Updated: 2024/02/01 14:21:47 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_specchar(char c)
{
	if (c == '$')
		return (DOLLAR);
	else if (c == '<')
		return (IN);
	else if (c == '>')
		return (OUT);
	else if (c == '|')
		return (PIPE);
	return (0);
}

t_tokens	init_tokens(t_token **tok_first, t_env *new_env, int exit_code)
{
	t_tokens	tokens;
	t_token		*tok;
	int			cnt;

	tok = *tok_first;
	tokens.first_tok = tok;
	cnt = 0;
	while (tok)
	{
		cnt ++;
		tok = tok->next;
	}
	tokens.tok_cnt = cnt;
	tokens.toks = tok_to_lst(tokens.first_tok, tokens.tok_cnt);
	if (!tokens.toks)
	{
		malloc_error(tok_first, NULL);
		return (tokens);
	}
	tokens.prev_exit = exit_code;
	tokens.env = new_env;
	tokens.error = 0;
	return (tokens);
}

int	add_pars_tok(t_token **tok_first, char *line, int *i)
{
	int	err;

	if (line[*i] == ' ')
		err = add_space(line, tok_first, i);
	else if (line[*i] == '\'')
		err = add_singquote(line, tok_first, i);
	else if (line[*i] == '\"')
		err = add_dblquote(line, tok_first, i);
	else if (is_specchar(line[*i]))
		err = add_specchar(line, tok_first, i);
	else
		err = add_str(line, tok_first, i);
	return (err);
}

t_token	*parser(char *line)
{
	int		i;
	t_token	*tok_first;
	int		err;

	i = 0;
	tok_first = NULL;
	while (line[i] != '\0')
	{
		err = add_pars_tok(&tok_first, line, &i);
		if (err != 0)
		{
			if (tok_first)
				tok_first->error = err;
			return (tok_first);
		}
	}
	if (tok_first && i >= 1 && (line[i - 1] == '|'
			|| line[i - 1] == '>' || line[i - 1] == '<'))
		tok_first->error = 258;
	return (tok_first);
}
