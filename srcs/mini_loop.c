/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:39:15 by rpliego           #+#    #+#             */
/*   Updated: 2024/02/08 12:58:58 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_executor(t_env **env, int prev_exit,
	t_token **new_tok, t_tokens *pars_tokens)
{
	t_tokens	exp_tokens;
	int			new_exit;

	exp_tokens = init_exp_tokens(new_tok, *env, prev_exit);
	if ((*new_tok)->error == MALLOC_ERROR)
	{
		free_tokens(pars_tokens, PARS);
		free_tokens(&exp_tokens, EXP);
		free_env(env);
		exit(1);
	}
	new_exit = executor(&exp_tokens);
	free_tokens(pars_tokens, PARS);
	free_tokens(&exp_tokens, EXP);
	if (new_exit == MALLOC_ERROR)
		exit (1);
	return (new_exit);
}

int	do_expander(t_env *env, int prev_exit, t_token *tok_first)
{
	t_tokens	pars_tokens;
	t_token		*new_tok;
	int			new_exit;

	new_exit = 0;
	pars_tokens = init_tokens(&tok_first, env, prev_exit);
	if (tok_first->error == MALLOC_ERROR)
		free_tok_env_exit(&tok_first, &env);
	new_tok = expander(&pars_tokens);
	if (!new_tok && pars_tokens.error == 0)
	{
		new_exit = prev_exit;
		free_tokens(&pars_tokens, PARS);
	}
	else if (pars_tokens.error == MALLOC_ERROR)
	{
		free_tokens(&pars_tokens, PARS);
		free_tok_env_exit(&new_tok, &env);
	}
	else if (pars_tokens.error != 0)
		new_exit = exp_error(&pars_tokens, &new_tok);
	else
		new_exit = do_executor(&env, prev_exit, &new_tok, &pars_tokens);
	return (new_exit);
}

int	new_exit(char *line, t_env *env, int prev_exit)
{
	t_token		*tok_first;
	int			new_exit;

	new_exit = 0;
	tok_first = parser(line);
	if (!tok_first || tok_first->error == MALLOC_ERROR)
		free_tok_env_exit(&tok_first, &env);
	else if (tok_first->error != 0)
	{
		new_exit = 258;
		print_error(tok_first->error);
		free_tok(&tok_first);
	}
	else
		new_exit = do_expander(env, prev_exit, tok_first);
	return (new_exit);
}

void	mini_loop(char *line, t_env *env)
{
	int	err_exit[2];

	err_exit[0] = 0;
	while (1)
	{
		do_signals(INTERACTIVE);
		do_sigign(SIGQUIT);
		line = readline("\033[1;33mмини-оболочка-0.1$\033[m ");
		do_sigign(SIGINT);
		if (!line)
		{
			if (isatty(STDIN_FILENO))
				write(2, "exit\n", 6);
			free_env(&env);
			exit(err_exit[0]);
		}
		if (ft_strlen(line) != 0)
		{
			err_exit[1] = new_exit(line, env, err_exit[0]);
			add_history(line);
			err_exit[0] = err_exit[1];
		}
		g_exit = 0;
		free(line);
	}
}
