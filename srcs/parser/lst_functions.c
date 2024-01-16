/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:05:07 by dkreise           #+#    #+#             */
/*   Updated: 2024/01/16 17:39:09 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*new_token(char *value, int type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	//malloc protection 
	new->value = value;
	new->type = type;
	new->next = NULL;
	return (new);
}

t_token	*token_last(t_token *tok)
{
	t_token	*last;

	last = tok;
	if (tok == NULL)
		return (NULL);
	while (tok->next != NULL)
	{
		tok = tok->next;
		last = tok;
	}
	return (last);
}

void	addback_token(t_token **tok, char *value, int type)
{
	t_token	*last;

	if (*tok == NULL)
		*tok = new_token(value, type);
	else
	{
		last = token_last(*tok);
		last->next = new_token(value, type);
	}
}

t_token	**tok_to_lst(t_token *tok, int tok_cnt)
{
	t_token **toks;
	int		i;

	i = 0;
	toks = malloc(sizeof(t_token *) * tok_cnt);
	while (i < tok_cnt)
	{
		toks[i] = tok;
		tok = tok->next;
		i ++;
	}
	return (toks);
}

t_tokens	init_tokens(t_token *tok_first, char **new_env)
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
	tokens.env = new_env;
	tokens.paths = get_paths(new_env);
	if (!tokens.paths)
		dprintf(2, "paths are null\n");
	// get_paths can return NULL
	tokens.initfd[0] = dup(STDIN_FILENO);
	tokens.initfd[1] = dup(STDOUT_FILENO);
	tokens.cmd_cnt = 0;
	return (tokens);
}
