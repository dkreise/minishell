/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:09:32 by dkreise           #+#    #+#             */
/*   Updated: 2024/01/03 18:58:08 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	add_space(char *line, t_token **tok_first, int i)
{
	char	*str;
	int	j;

	str = ft_substr(line, i, 1);
	addback_token(tok_first, str, 1);
	j = 0;
	while (line[i] == ' ' && line[i] != '\0')
	{
		i ++;
		j ++;
	}
	return (j);
}

int	add_singquote(char *line, t_token **tok_first, int i)
{
	char	*str;
	int		start;

	start = i;
	i ++;
	str = NULL; //delete later
	while (line[i] != '\'' && line[i] != '\0')
		i ++;
	if (line[i] == '\'')
		str = ft_substr(line, start, i - start + 1);
	// else if (line[i] == '\0') error of unclosed quote
	addback_token(tok_first, str, 2);
	return (i - start + 1);
}

int	add_dblquote(char *line, t_token **tok_first, int i)
{
	char	*str;
	int		start;

	start = i;
	i ++;
	str = NULL; //delete later
	while (line[i] != '\"' && line[i] != '\0')
		i ++;
	if (line[i] == '\"')
		str = ft_substr(line, start, i - start + 1);
	// else if (line[i] == '\0') error of unclosed quote
	addback_token(tok_first, str, 2);
	return (i - start + 1);
}

int add_specchar(char *line, t_token **tok_first, int i)
{
	char	*str;

	str = ft_substr(line, i, 1);
	addback_token(tok_first, str, 4);
	return (1);
}

int	add_str(char *line, t_token **tok_first, int i)
{
	char	*str;
	int		start;

	start = i;
	i ++;
	while (line[i] != '$' && line[i] != '>' && line[i] != '<' && line[i] != '|' && line[i] != '\'' && line[i] != '\"' && line[i] != ' ' && line[i] != '\0')
		i ++;
	str = ft_substr(line, start, i - start);
	addback_token(tok_first, str, 0);
	return (i - start);
}

int	main(void)
{
	char	*line;
	int		i;
	t_token	*tok_first;

	line = readline("minishell> ");
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
		else if (line[i] == '$' || line[i] == '>' || line[i] == '<' || line[i] == '|')
			i += add_specchar(line, &tok_first, i);
		else
			i += add_str(line, &tok_first, i);
	}
	while (tok_first != NULL)
	{
		printf("type: %i value: %s.\n", tok_first->type, tok_first->value);
		tok_first = tok_first->next;
	}
	return (0);
}



