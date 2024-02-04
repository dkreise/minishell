/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:35:01 by dkreise           #+#    #+#             */
/*   Updated: 2024/02/04 12:37:42 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_lst(char **lst)
{
	int	i;

	i = 0;
	if (lst)
	{
		while (lst[i])
		{
			free(lst[i]);
			i ++;
		}
		free(lst);
	}
}

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*cur;
	t_cmd	*freed;
	int		i;

	cur = *cmd;
	i = 0;
	while (cur)
	{
		if (cur->args)
		{
			i = 0;
			while (cur->args[i])
			{
				free(cur->args[i]);
				i ++;
			}
			free(cur->args);
		}
		freed = cur;
		cur = cur->prev;
		free(freed);
	}
}

void	free_tok(t_token **tok)
{
	t_token	*cur;
	t_token	*tnext;

	cur = *tok;
	while (cur)
	{
		tnext = cur->next;
		free(cur->value);
		free(cur);
		cur = tnext;
	}
}

void	free_env(t_env **env)
{
	t_env	*cur;
	t_env	*enext;

	cur = *env;
	while (cur)
	{
		enext = cur->next;
		free(cur->data);
		free(cur);
		cur = enext;
	}
}

void	free_paths(t_tokens *tokens)
{
	int	i;

	i = 0;
	if (tokens->paths)
	{
		while (tokens->paths[i])
		{
			free(tokens->paths[i]);
			i ++;
		}
		free(tokens->paths);
	}
}
