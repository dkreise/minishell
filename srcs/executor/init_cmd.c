/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 19:11:52 by dkreise           #+#    #+#             */
/*   Updated: 2024/01/09 19:14:26 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	args_cnt(t_tokens *tokens, int i)
{
	int	cnt;

	cnt = 0;
	while (i < tokens->tok_cnt)
	{
		if (tokens->toks[i]->type < 5)
			cnt ++;
		else 
			return (cnt);
		i ++;
	}
	return (cnt);
}

t_cmd	init_cmd(t_tokens *tokens, int i)
{
	t_cmd	cmd;
	int		j;

	cmd.args = ft_calloc(args_cnt(tokens, i) + 1, sizeof(char *));
	j = 0;
	if (tokens->toks[i]->type >= 5)
		tokens->toks[i]->type -= 5;
	while (i < tokens->tok_cnt)
	{
		if (tokens->toks[i]->type == 0)
		{
			cmd.args[j] = ft_strdup(tokens->toks[i]->value);
			// malloc protection
			j ++;
		}
		else if (tokens->toks[i]->type >= 5)
			break ;
		// else     init_pipe
		i ++;
	}
	return (cmd);
}
