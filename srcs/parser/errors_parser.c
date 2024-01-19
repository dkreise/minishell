/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:04:49 by dkreise           #+#    #+#             */
/*   Updated: 2024/01/19 14:26:22 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_toklst(t_token **tok)
{
	t_token	*prev;

	while (*tok)
	{
		free((*tok)->value);
		prev = *tok;
		*tok = (*tok)->next;
		free(prev);
	}
}

void	parser_error(char *msg, t_token **tok, int exit_code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	(*tok)->error = exit_code;
	//free_toklst(tok);
	//exit(exit_code);
}
