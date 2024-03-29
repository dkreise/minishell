/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:04:49 by dkreise           #+#    #+#             */
/*   Updated: 2024/01/26 14:35:10 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	malloc_error(t_token **tok_first, t_tokens *tokens)
{
	ft_putstr_fd("minishell: memory allocation error\n", 2);
	if (tok_first)
		(*tok_first)->error = MALLOC_ERROR;
	else if (tokens)
		tokens->error = MALLOC_ERROR;
}

void	print_error(int tok_char)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	if (tok_char == PIPE)
		ft_putstr_fd("`|'\n", 2);
	else if (tok_char == IN)
		ft_putstr_fd("`<'\n", 2);
	else if (tok_char == OUT)
		ft_putstr_fd("`>'\n", 2);
	else
		ft_putstr_fd("`newline'\n", 2);
}
