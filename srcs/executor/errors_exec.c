/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:26:29 by dkreise           #+#    #+#             */
/*   Updated: 2024/02/04 16:02:19 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exp_error(t_tokens *pars_tokens, t_token **new_tok)
{
	print_error(pars_tokens->error);
	free_tokens(pars_tokens, PARS);
	free_tok(new_tok);
	return (258);
}

void	free_tok_env_exit(t_token **tok_first, t_env **env)
{
	free_tok(tok_first);
	free_env(env);
	exit(1);
}

void	free_tokens(t_tokens *tokens, int type)
{
	free_tok(&(tokens->first_tok));
	free(tokens->toks);
	if (type == EXP)
	{
		free_paths(tokens);
	}
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
		free_paths(tokens);
		free_cmd(&cmd);
		exit(exit_code);
	}
}
