/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:24:30 by dkreise           #+#    #+#             */
/*   Updated: 2024/01/25 17:32:25 by dkreise          ###   ########.fr       */
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
	return (addback_token(tok_first, str, SPACE));
}

int	add_singquote(char *line, t_token **tok_first, int *ind)
{
	char	*str;
	int		start;
	int		i;
	int		err;

	i = *ind;
	err = 0;
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
			return (MALLOC_ERROR);
		}
	}
	else
	{
		err = addback_token(tok_first, str, SNGL_Q);
		return (258);
	}
	*ind = *ind + (i - start + 1);
	return (addback_token(tok_first, str, SNGL_Q));
}

int	add_dblquote(char *line, t_token **tok_first, int *ind)
{
	char	*str;
	int		start;
	int		i;
	int		err;

	i = *ind;
	err = 0;
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
			return (MALLOC_ERROR);
		}
	}
	else
	{
		err = addback_token(tok_first, str, DBL_Q);
		return (258);
	}
	*ind = *ind + (i - start + 1);
	return (addback_token(tok_first, str, DBL_Q));
}

int add_specchar(char *line, t_token **tok_first, int *ind)
{
	char	*str;
	int		i;

	i = *ind;
	str = ft_substr(line, i, 1);
	if (str == NULL)
	{
		malloc_error(tok_first, NULL);
		return (MALLOC_ERROR);
	}
	*ind = *ind + 1;
	return (addback_token(tok_first, str, is_specchar(line[i])));
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
