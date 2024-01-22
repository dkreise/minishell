/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:09:32 by dkreise           #+#    #+#             */
/*   Updated: 2024/01/22 15:43:23 by dkreise          ###   ########.fr       */
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
t_tokens	init_tokens(t_token *tok_first, t_env *new_env, int exit_code)
{
	t_tokens	tokens;
	int			cnt;

	tokens.first_tok = tok_first;
	cnt = 0;
	while (tok_first)
	{
		cnt ++;
		tok_first = tok_first->next;
	}
	tokens.tok_cnt = cnt;
	tokens.toks = tok_to_lst(tokens.first_tok, tokens.tok_cnt);
	if (!tokens.toks)
	{
		malloc_error(&tok_first);
		return (tokens);
	}
	tokens.prev_exit = exit_code;
	tokens.env = new_env;
	tokens.error = 0;
	return (tokens);
}

t_token	*parser(char *line)
{
	int		i;
	t_token	*tok_first;

	i = 0;
	tok_first = NULL;
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
			i += add_space(line, &tok_first, i);
		else if (line[i] == '\'')
			i += add_singquote(line, &tok_first, i);
		else if (line[i] == '\"')
			i += add_dblquote(line, &tok_first, i);
		else if (is_specchar(line[i]))
			i += add_specchar(line, &tok_first, i);
		else
			i += add_str(line, &tok_first, i);
		if (tok_first->error != 0)
			return (tok_first);
	}
	if (i >= 1 && (line[i - 1] == '|' || line[i - 1] == '>' || line[i - 1] == '<'))
		tok_first->error = 258;
	return(tok_first); 
}
