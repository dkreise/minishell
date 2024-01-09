/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:50:18 by rpliego           #+#    #+#             */
/*   Updated: 2024/01/09 19:33:19 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//~~~~~~~~~~~~~~~~INCLUDES~~~~~~~~~~~~~~//
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <libft.h>

//~~~~~~~~~~~~~~~~COLORS~~~~~~~~~~~~~~//
# define E "\033[m"			//end
# define R "\033[1;31m"		//red
# define G "\033[1;32m"		//green
# define Y "\033[1;33m"		//yellow
# define B "\033[1;34m"		//blue
# define T "\033[1;35m"		//Turquesa
# define C "\033[1;36m"		//Cyan
# define O "\033[38;5;208m"	//orange
# define F "\033[38;5;128m" //purple

# define NONE 0
# define FIRST 1
# define SECOND 2
# define BOTH 3
# define NOENV "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/Applicat\
ions/VMware Fusion.app/Contents/Public:/usr/local/go/bin:/usr/local/munki"

// TYPE: 0:str, 1:space, 2:' ', 3:" ", 4:>,<,|,$
typedef struct s_token
{
	char			*value;
	int 			type;
	struct s_token	*next;
} t_token;

//struct I need for executor:

typedef struct s_tokens
{
	t_token *first_tok;
	t_token	**toks;
	int		tok_cnt;
	char	**env;
	char	**paths;

} t_tokens;
/*
types of tokens: 0:none, 1:<, 2:>, 3:<<, 4:>>, AFTER PIPE 5:none, 6:<, 7:>,
	8:<<, 9:>> 
example: ls -la | cat | cat >> file1   -->   ls:0 -la:0 cat:5 cat:5 file1:4 
*/

typedef struct s_cmd
{
	char	**args;
	//char	*
	//struct s_cmd	*next;
} t_cmd;

//~~~~~~~~~~~~~~~~PARSER~~~~~~~~~~~~~~//
t_token	*new_token(char *value, int type);
t_token	*token_last(t_token *tok);
void	addback_token(t_token **tok, char *value, int type);
int		add_space(char *line, t_token **tok_first, int i);
int		add_singquote(char *line, t_token **tok_first, int i);
int		add_dblquote(char *line, t_token **tok_first, int i);
int		add_specchar(char *line, t_token **tok_first, int i);
int		add_str(char *line, t_token **tok_first, int i);
int		is_specchar(char c);
void	parser_error(char *msg, t_token **tok, int exit_code);

//~~~~~~~~~~~~~~~~EXECUTOR~~~~~~~~~~~~~~//
t_token	**tok_to_lst(t_token *tok, int tok_cnt);
int		args_cnt(t_tokens *tokens, int i);
t_cmd	init_cmd(t_tokens *tokens, int i);

#endif
