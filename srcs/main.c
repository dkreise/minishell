/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:44:44 by rpliego           #+#    #+#             */
/*   Updated: 2024/01/29 19:56:39 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_header(void)
{
	printf("%s           _       _     _          _ _ \n", F);
	printf("%s _ __ ___ (_)_ __ (_)___| |__   ___| | |\n", F);
	printf("%s| '_ ` _ || | '_ `| / __| '_ ` / _ | | |\n", F);
	printf("%s| | | | | | | | | | |__ | | | |  __/ | |\n", F);
	printf("%s|_| |_| |_|_|_| |_|_|___/_| |_||___|_|_|\n\n\n", F);
}

int	new_exit(char *line, t_env *env, int prev_exit)
{
	t_token		*tok_first;
	t_tokens	pars_tokens;
	t_token		*new_tok;
	t_tokens	exp_tokens;
	int			new_exit;

	new_exit = 0;
	tok_first = parser(line);
	if (!tok_first || tok_first->error == MALLOC_ERROR)
	{
		free_tok(&tok_first);
		free_env(&env);
		exit(1);
	}
	else if (tok_first->error != 0)
	{
		new_exit = tok_first->error;
		print_error(tok_first->error);
		free_tok(&tok_first);
	}
	else
	{
		pars_tokens = init_tokens(&tok_first, env, prev_exit);
		if (tok_first->error == MALLOC_ERROR)
		{
			free_tok(&tok_first);
			free_env(&env);
			exit(1);
		}
		new_tok = expander(&pars_tokens);
		if (!new_tok && pars_tokens.error == 0)
		{
			new_exit = prev_exit;
			free_tokens(&pars_tokens, PARS);
		}
		else if (pars_tokens.error == MALLOC_ERROR)
		{
			free_tokens(&pars_tokens, PARS);
			free_tok(&new_tok);
			free_env(&env);
			exit(1);
		}
		else if (pars_tokens.error != 0)
		{
			new_exit = 258;
			print_error(pars_tokens.error);
			free_tokens(&pars_tokens, PARS);
			free_tok(&new_tok);
		}
		else
		{
			exp_tokens = init_exp_tokens(&new_tok, env, prev_exit);
			if (new_tok->error == MALLOC_ERROR)
			{
				// free smth
				free_tokens(&pars_tokens, PARS);
				free_tokens(&exp_tokens, EXP);
				free_env(&env);
				exit(1);
			}
			new_exit = executor(&exp_tokens);
			free_tokens(&pars_tokens, PARS);
			free_tokens(&exp_tokens, EXP);
		}
	}
	return (new_exit);
}

int	main(int ac, char **av, char **environment)
{
	char	*line;
	t_env	*env;
	int		err_exit[2];

	(void)av;
	line = NULL;
	if (ac > 1)
	{
		ft_putstr_fd("ONLY ./minishell\n", 2);
		return (1);
	}
	//print_header();
	if (*environment == NULL)
		env = our_env();
	else
		env = dup_env(environment);
	err_exit[0] = 0;
	g_exit = 0;
	mini_loop(line, env, err_exit);
	return (0);
}
