/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:24:30 by dkreise           #+#    #+#             */
/*   Updated: 2024/01/23 14:42:22 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	add_space(char *line, t_token **tok_first, int i)
{
	char	*str;
	int		j;

	str = ft_substr(line, i, 1);
	if (str == NULL)
	{
		malloc_error(tok_first, NULL);
		return (1);
	}
	addback_token(tok_first, str, SPACE);
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
	str = NULL;
	while (line[i] != '\'' && line[i] != '\0')
		i ++;
	if (line[i] == '\'')
	{
		str = ft_substr(line, start, i - start + 1);
		if (str == NULL)
		{
			malloc_error(tok_first, NULL);
			return (1);
		}
	}
	else
		(*tok_first)->error = 258;
	addback_token(tok_first, str, SNGL_Q);
	return (i - start + 1);
}

int	add_dblquote(char *line, t_token **tok_first, int i)
{
	char	*str;
	int		start;

	start = i;
	i ++;
	str = NULL;
	while (line[i] != '\"' && line[i] != '\0')
		i ++;
	if (line[i] == '\"')
	{
		str = ft_substr(line, start + 1, i - start - 1);
		if (str == NULL)
		{
			malloc_error(tok_first, NULL);
			return (1);
		}
	}
	else
		(*tok_first)->error = 258;
	addback_token(tok_first, str, DBL_Q);
	return (i - start + 1);
}

int add_specchar(char *line, t_token **tok_first, int i)
{
	char	*str;

	str = ft_substr(line, i, 1);
	if (str == NULL)
	{
		malloc_error(tok_first, NULL);
		return (1);
	}
	addback_token(tok_first, str, is_specchar(line[i]));
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
	if (str == NULL)
	{
		malloc_error(tok_first, NULL);
		return (1);
	}
	addback_token(tok_first, str, NONE);
	return (i - start);
}
