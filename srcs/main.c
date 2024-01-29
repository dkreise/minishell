/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:44:44 by rpliego           #+#    #+#             */
/*   Updated: 2024/01/29 11:09:04 by dkreise          ###   ########.fr       */
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

char *update_shlvl(char *str)
{
	int	ato;

	while (*str != '=' && *str)
		str++;
	str++;
	ato = ft_atoi(str);
	ato += 1;
	return (ft_strjoin("SHLVL=", ft_itoa(ato), 4));
}

t_env	*dup_env(char **env_array)
{
	t_env *first;
	t_env *env;
	t_env *new;
	int	i;

	if (!env_array)
		return (NULL);
	first = malloc(sizeof(t_env));
	if (!first)
		return (NULL);
	first->data = ft_strdup(env_array[0]);
	first->unset_flag = 0;
	first->next = NULL;
	env = first;
	i = 0;
	while (env_array[++i] != NULL)
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (NULL);
		if (ft_strncmp("SHLVL", env_array[i], 5) == 0)
		{
			//printf("entrooooo\n\n");
			new->data = ft_strdup(update_shlvl(env_array[i]));
			//printf("------%s------\n", new->data);
		}
		else
			new->data = ft_strdup(env_array[i]);
		new->unset_flag = 0;
		new->next = NULL;
		env->next = new;
		env = new;
	}
	return (first);
}

int	check_blt(char *cmd)
{
	if (cmd)
	{
		if (ft_strncmp(cmd, "env", 4) == 0)
			return (1);
		if (ft_strncmp(cmd, "export", 7) == 0)
			return (1);
		if (ft_strncmp(cmd, "unset", 6) == 0)
			return (1);
		if (ft_strncmp(cmd, "pwd", 4) == 0)
			return (1);
		if (ft_strncmp(cmd, "cd", 3) == 0)
			return (1);
		if (ft_strncmp(cmd, "exit", 6) == 0)
			return (1);
		if (ft_strncmp(cmd, "echo", 5) == 0)
			return (1);
	}
	return (0);
}

void	exec_blt(char **cmd, t_env *env)
{
	if (ft_strncmp(cmd[0], "env", 4) == 0)
		ft_env(env);
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
		ft_export(cmd, &env);
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		ft_unset(cmd, &env);
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(cmd[0], "cd", 3) == 0)
		ft_cd(cmd, env);
	else if (ft_strncmp(cmd[0], "exit", 6) == 0)
		ft_exit(cmd);
	else if (ft_strncmp(cmd[0], "echo", 5) == 0)
		ft_echo(cmd);
}

void	print_toklst(char *header, t_token *tok_first)
{
	dprintf(2, "%s\n", header);
	while (tok_first != NULL)
	{
		printf("type: %i value: %s.\n", tok_first->type, tok_first->value);
		tok_first = tok_first->next;
	}
}

void	free_tok_env_exit(t_token **tok_first, t_env **env)
{
	free_tok(tok_first);
	free_env(env);
	exit(1);
}

int	exp_error(t_tokens *pars_tokens, t_token **new_tok)
{
	print_error(pars_tokens->error);
	free_tokens(pars_tokens, PARS);
	free_tok(new_tok);
	return (258);
}

int	do_executor(t_env **env, int prev_exit, t_token **new_tok, t_tokens *pars_tokens)
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
	//print_toklst("EXPANDER", new_tok);
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
	//print_toklst("PARSER", tok_first);
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

t_env	*our_env(void)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->data = ft_strdup("SHLVL=1");
	env->unset_flag = 0;
	env->next = NULL;
	return (env);
}

void update_global(int *err_exit)
{
	if (g_exit > 0)
	{
		g_exit = 0;
		err_exit[0] = 1;
	}
}

int main(int ac, char **av, char **environment)
{
	char	*line;
	t_env	*env;
	int			err_exit[2];

	(void)ac;
	(void)av;
	//print_header();
	if (*environment == NULL)
		env = our_env();
	else
		env = dup_env(environment);
	err_exit[0] = 0;
	g_exit = 0;
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
		    exit(0);
		}
		if (ft_strlen(line) != 0)
		{
			err_exit[1] = new_exit(line, env, err_exit[0]);
			add_history(line);
			err_exit[0] = err_exit[1];
		}
		// dprintf(2, "exit: %i\n", err_exit[0]);
		// dprintf(2, "gl: %i\n", g_exit);
		//update_global(err_exit);
		g_exit = 0;
		// dprintf(2, "exit: %i\n", err_exit[0]);
		// dprintf(2, "gl: %i\n", g_exit);
		free(line);
	}
	return (0);
}

/*
int	new_exit(char *line, t_env *env, int prev_exit)
{
	t_token		*tok_first;
	int			new_exit;

	new_exit = 0;
	tok_first = parser(line);
	//print_toklst("PARSER", tok_first);
	if (!tok_first || tok_first->error == MALLOC_ERROR)
		free_tok_env_exit(&tok_first, &env);
	else if (tok_first->error != 0)
	{
		new_exit = tok_first->error;
		print_error(tok_first->error);
		free_tok(&tok_first);
	}
	else
	{
		// pars_tokens = init_tokens(&tok_first, env, prev_exit);
		// if (tok_first->error == MALLOC_ERROR)
		// 	free_tok_env_exit(&tok_first, &env);
		// new_tok = expander(&pars_tokens);
		// //print_toklst("EXPANDER", new_tok);
		// if (!new_tok && pars_tokens.error == 0)
		// {
		// 	new_exit = prev_exit;
		// 	free_tokens(&pars_tokens, PARS);
		// }
		// else if (pars_tokens.error == MALLOC_ERROR)
		// {
		// 	free_tokens(&pars_tokens, PARS);
		// 	free_tok_env_exit(&new_tok, &env);
		// }
		// else if (pars_tokens.error != 0)
		// {
		// 	new_exit = 258;
		// 	print_error(pars_tokens.error);
		// 	free_tokens(&pars_tokens, PARS);
		// 	free_tok(&new_tok);
		// }
		// else
		// {
		// 	// exp_tokens = init_exp_tokens(&new_tok, env, prev_exit);
		// 	// if (new_tok->error == MALLOC_ERROR)
		// 	// {
		// 	// 	free_tokens(&pars_tokens, PARS);
		// 	// 	free_tokens(&exp_tokens, EXP);
		// 	// 	free_env(&env);
		// 	// 	exit(1);
		// 	// }
		// 	// new_exit = executor(&exp_tokens);
		// 	// free_tokens(&pars_tokens, PARS);
		// 	// free_tokens(&exp_tokens, EXP);
		// 	// if (new_exit == MALLOC_ERROR)
		// 	// 	exit (1);
		// 	new_exit = do_executor(&env, prev_exit, &new_tok, &pars_tokens);
		// }
		new_exit = do_expander(env, prev_exit, tok_first);
	}
	return (new_exit);
}
*/