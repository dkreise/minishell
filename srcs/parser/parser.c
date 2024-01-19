/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:09:32 by dkreise           #+#    #+#             */
/*   Updated: 2024/01/19 14:07:10 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_specchar(char c)
{
	//if (c == '$' || c == '>' || c == '<' || c == '|')
	//	return (1);
	if (c == '$')
		return (DOLLAR);
	else if (c == '<')
		return (IN);
	else if (c == '>')
		return (OUT);
	else if (c == '|')
		return (PIPE);
	return (0);
}
t_tokens	init_tokens(t_token *tok_first, int exit_code)
{
	t_tokens	tokens;
	int			cnt;

	tokens.first_tok = tok_first;
	cnt = 0;
	while (tok_first)
	{
		cnt ++;
		tok_first = tok_first->next;
	}
	tokens.tok_cnt = cnt;
	tokens.toks = tok_to_lst(tokens.first_tok, tokens.tok_cnt);
	tokens.prev_exit = exit_code;
	/*tokens.env = new_env;
	tokens.paths = get_paths(generate_arr(linked list)); //instead of getpaths, pass as an
	 // argument a function that creates a double array from a linked list
	if (!tokens.paths)
		dprintf(2, "paths are null\n");
	// get_paths can return NULL
	tokens.initfd[0] = dup(STDIN_FILENO);
	tokens.initfd[1] = dup(STDOUT_FILENO);
	tokens.cmd_cnt = 0;*/
	return (tokens);
}

t_token	*parser(char *line)
{
	int		i;
	t_token	*tok_first;

	i = 0;
	tok_first = NULL;
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
			i += add_space(line, &tok_first, i);
		else if (line[i] == '\'')
			i += add_singquote(line, &tok_first, i);
		else if (line[i] == '\"')
			i += add_dblquote(line, &tok_first, i);
		else if (is_specchar(line[i]))
			i += add_specchar(line, &tok_first, i);
		else
			i += add_str(line, &tok_first, i);
		if (tok_first->error != 0)
			break ;
	}
	// if line[i-1] == '|' syntax error 
	if (line[i - 1] == '|' || line[i - 1] == '>' || line[i - 1] == '<')
		parser_error("syntax error near unexpected token `newline'\n", &tok_first, 258);
	// (???) if line[i-1] == '$' -> error: no such file or directory (???)
	return(tok_first); 
}
/*
int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char	*line;
	t_token	*tok_first;

	line = readline("\033[1;33mмини-оболочка-0.1$\033[m ");
	tok_first = parser(line);
	t_tokens tokens = init_tokens(tok_first, env);
	printf("PARSER:\n");
	while (tok_first != NULL)
	{
		printf("type: %i value: %s.\n", tok_first->type, tok_first->value);
		tok_first = tok_first->next;
	}
	t_token *new_tok = expander(&tokens);
	printf("EXPANDER:\n");
	while (new_tok != NULL)
	{
		printf("type: %i value: %s.\n", new_tok->type, new_tok->value);
		new_tok = new_tok->next;
	}
	return (0);
}*/
