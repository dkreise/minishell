/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:26:29 by dkreise           #+#    #+#             */
/*   Updated: 2024/02/03 19:33:16 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_lst(char **lst)
{
	int	i;

	i = 0;
	if (lst)
	{
		//dprintf(2, "freeing char list!!\n");
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

	int j = 0;
	cur = *cmd;
	i = 0;
	while (cur)
	{
		dprintf(2, "i:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::%i\n", j);
		dprintf(2, "value:%s|\n", cur->args[0]);
		//dprintf(2, "freeing cmd!!\n");
		if (cur->args)
		{
			i = 0;
			while (cur->args[i])
			{
				//dprintf(2, "freeing args of cmd!! %p\n", cur->args[i]);
				free(cur->args[i]);
				i ++;
			}
			free(cur->args);
		}
		freed = cur;
		cur = cur->prev;
		j++;
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
		//dprintf(2, "freeing tok!!\n");
		tnext = cur->next;
		dprintf(2, "tok pointer that is freed:: %p\n", cur->value);
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
		//dprintf(2, "freeing env!!\n");
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
		//dprintf(2, "freeing psths!!\n");
		while (tokens->paths[i])
		{
			free(tokens->paths[i]);
			i ++;
		}
		free(tokens->paths);
	}
}

void	free_tokens(t_tokens *tokens, int type)
{
	free_tok(&(tokens->first_tok));
	free(tokens->toks);
	if (type == EXP)
	{
		free_paths(tokens);
	}
	//dprintf(2, "tokens freed?....\n");
}

void	exit_error(char *arg, char *msg, t_tokens *tokens, t_cmd *cmd)
{
	int	exit_code;

	exit_code = cmd->exit_code;
	(void)tokens;
	write(2, "minishell: ", ft_strlen("minishell: "));
	if (msg)
	{
		if (arg)
		{
			write(2, arg, ft_strlen(arg));
			write(2, ": ", 2);
		}
		write(2, msg, ft_strlen(msg));
	}
	else
		perror(arg);
	if (exit_code == 127)
	{
		free_env(&(tokens->env));
		free_paths(tokens);
		free_cmd(&cmd);
		exit(exit_code);
	}
}
