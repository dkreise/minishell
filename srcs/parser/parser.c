/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:09:32 by dkreise           #+#    #+#             */
/*   Updated: 2024/01/09 15:43:35 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_specchar(char c)
{
	if (c == '$' || c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
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
	}
	// if line[i-1] == '|' syntax error 
	if (line[i - 1] == '|' || line[i - 1] == '>' || line[i - 1] == '<')
		parser_error("syntax error near unexpected token `newline'\n", &tok_first, 258);
	// (???) if line[i-1] == '$' -> error: no such file or directory (???)
	return(tok_first); 
}
/*
int	main(void)
{
	char	*line;
	t_token	*tok_first;

	line = readline("\033[1;33mмини-оболочка-0.1$\033[m ");
	tok_first = parser(line);
	while (tok_first != NULL)
	{
		printf("type: %i value: %s.\n", tok_first->type, tok_first->value);
		tok_first = tok_first->next;
	}
	return (0);
}*/
