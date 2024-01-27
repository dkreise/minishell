/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:24:30 by dkreise           #+#    #+#             */
/*   Updated: 2024/01/27 15:45:36 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	add_space(char *line, t_token **tok_first, int *ind)
{
	char	*str;
	int		j;
	int		i;

	i = *ind;
	str = ft_substr(line, i, 1);
	if (str == NULL)
	{
		malloc_error(tok_first, NULL);
		return (MALLOC_ERROR);
	}
	j = 0;
	while (line[i] == ' ' && line[i] != '\0')
	{
		i ++;
		j ++;
	}
	*ind = *ind + j;
	return (addback_token(tok_first, str, SPACET));
}

int	add_singquote(char *line, t_token **tok_first, int *i)
{
	char	*str;
	int		start;

	start = *i;
	str = NULL;
	*i = *i + 1;
	while (line[*i] != '\'' && line[*i] != '\0')
		*i = *i + 1;
	if (line[*i] == '\'')
	{
		str = ft_substr(line, start, *i - start + 1);
		if (str == NULL)
		{
			malloc_error(tok_first, NULL);
			return (MALLOC_ERROR);
		}
	}
	else
	{
		addback_token(tok_first, str, SNGL_Q);
		return (258);
	}
	*i = *i + 1;
	return (addback_token(tok_first, str, SNGL_Q));
}

int	add_dblquote(char *line, t_token **tok_first, int *i)
{
	char	*str;
	int		start;

	start = *i;
	*i = *i + 1;
	str = NULL;
	while (line[*i] != '\"' && line[*i] != '\0')
		*i = *i + 1;
	if (line[*i] == '\"')
	{
		str = ft_substr(line, start + 1, *i - start - 1);
		if (str == NULL)
		{
			malloc_error(tok_first, NULL);
			return (MALLOC_ERROR);
		}
	}
	else
	{
		addback_token(tok_first, str, DBL_Q);
		return (258);
	}
	*i = *i + 1;
	return (addback_token(tok_first, str, DBL_Q));
}

int add_specchar(char *line, t_token **tok_first, int *i)
{
	char	*str;

	str = ft_substr(line, *i, 1);
	if (str == NULL)
	{
		malloc_error(tok_first, NULL);
		return (MALLOC_ERROR);
	}
	*i = *i + 1;
	return (addback_token(tok_first, str, is_specchar(line[*i - 1])));
}

int	add_str(char *line, t_token **tok_first, int *ind)
{
	char	*str;
	int		start;
	int		i;

	i = *ind;
	start = i;
	i ++;
	while (!is_specchar(line[i]) && line[i] != '\'' && line[i] != '\"'
		&& line[i] != ' ' && line[i] != '\0')
		i ++;
	str = ft_substr(line, start, i - start);
	if (str == NULL)
	{
		malloc_error(tok_first, NULL);
		return (MALLOC_ERROR);
	}
	*ind = *ind + (i - start);
	return (addback_token(tok_first, str, NONE));
}
