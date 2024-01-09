/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:24:30 by dkreise           #+#    #+#             */
/*   Updated: 2024/01/08 12:13:52 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	add_space(char *line, t_token **tok_first, int i)
{
	char	*str;
	int	j;

	str = ft_substr(line, i, 1);
	//malloc protection
	if (str == NULL)
		parser_error("memory allocation error\n", tok_first, 1);
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
	str = NULL; //delete later (now not defined in each case)
	while (line[i] != '\'' && line[i] != '\0')
		i ++;
	if (line[i] == '\'')
	{
		str = ft_substr(line, start, i - start + 1);
		//malloc protection
		if (str == NULL)
		parser_error("memory allocation error\n", tok_first, 1);
	}
	// else if (line[i] == '\0') error of unclosed quote (exit code 258?)
	else
		parser_error("syntax error (unclosed quote error)\n", tok_first, 1);
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
	{
		str = ft_substr(line, start, i - start + 1);
		//malloc protection
		if (str == NULL)
			parser_error("memory allocation error\n", tok_first, 1);
	}
	// else if (line[i] == '\0') error of unclosed quote (exit code 258?)
	else
		parser_error("syntax error (unclosed quote error)\n", tok_first, 1);
	addback_token(tok_first, str, 2);
	return (i - start + 1);
}

int add_specchar(char *line, t_token **tok_first, int i)
{
	char	*str;

	str = ft_substr(line, i, 1);
	//malloc protection
	if (str == NULL)
		parser_error("memory allocation error\n", tok_first, 1);
	addback_token(tok_first, str, 4);
	return (1);
}

int	add_str(char *line, t_token **tok_first, int i)
{
	char	*str;
	int		start;

	start = i;
	i ++;
	while (!is_specchar(line[i]) && line[i] != '\'' && line[i] != '\"'
		&& line[i] != ' ' && line[i] != '\0')
		i ++;
	str = ft_substr(line, start, i - start);
	//malloc protection
	if (str == NULL)
		parser_error("memory allocation error\n", tok_first, 1);
	addback_token(tok_first, str, 0);
	return (i - start);
}
