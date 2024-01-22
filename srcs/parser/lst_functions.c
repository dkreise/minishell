/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:05:07 by dkreise           #+#    #+#             */
/*   Updated: 2024/01/22 14:29:08 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*new_token(char *value, int type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	//malloc protection 
	new->value = value;
	new->type = type;
	new->next = NULL;
	new->hd_file = -1;
	new->error = 0;
	return (new);
}

t_token	*token_last(t_token *tok)
{
	t_token	*last;

	last = tok;
	if (tok == NULL)
		return (NULL);
	while (tok->next != NULL)
	{
		tok = tok->next;
		last = tok;
	}
	return (last);
}

void	addback_token(t_token **tok, char *value, int type)
{
	t_token	*last;

	if (*tok == NULL)
		*tok = new_token(value, type);
	else
	{
		last = token_last(*tok);
		last->next = new_token(value, type);
	}
}

t_token	**tok_to_lst(t_token *tok, int tok_cnt)
{
	t_token **toks;
	int		i;

	i = 0;
	toks = malloc(sizeof(t_token *) * tok_cnt);
	if (!toks)
		return (NULL);
	while (i < tok_cnt)
	{
		toks[i] = tok;
		tok = tok->next;
		i ++;
	}
	return (toks);
}


char	**lst_to_arr(t_env *env)
{
	int		cnt;
	int		i;
	char	**env_arr;
	t_env	*env_first;

	cnt = 0;
	i = 0;
	env_first = env;
	while (env)
	{
		if (env->unset_flag == 0)
			cnt ++;
		env = env->next;
	}
	env_arr = ft_calloc(sizeof(char *), cnt + 1);
	// malloc protection
	while (env_first)
	{
		if (env_first->unset_flag == 0)
		{
			env_arr[i] = ft_strdup(env_first->data);
			// malloc protection
			i ++;
		}
		env_first = env_first->next;
	}
	return(env_arr);
}

