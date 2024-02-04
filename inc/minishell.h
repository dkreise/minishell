/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:50:18 by rpliego           #+#    #+#             */
/*   Updated: 2024/02/04 16:12:25 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//~~~~~~~~~~~~~~~~INCLUDES~~~~~~~~~~~~~~//
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <libft.h>

# define TRUE 1
# define FALSE 0
# define PARS 1
# define EXP 2
# define MALLOC_ERROR 42

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

//~~~~~~~~~~~~~~~~SIGNALS MACROS~~~~~~~~~~~~~~//
# define INTERACTIVE 1
# define NON_STANDAR 2
# define HERDOC 3

# define TRUE 1
# define FALSE 0

# define NONE 0
# define FIRST 1
# define SECOND 2
# define BOTH 3
# define NOENV "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/Applicat\
ions/VMware Fusion.app/Contents/Public:/usr/local/go/bin:/usr/local/munki"

# define SPACET 1
# define SNGL_Q 2
# define DBL_Q 3
# define DOLLAR 4
# define IN 5
# define OUT 6
# define HEREDOC 7
# define APPEND_OUT 8
# define PIPE 9
# define PIPE_IN 14
# define PIPE_OUT 15
# define PIPE_HEREDOC 16
# define PIPE_APPEND_OUT 17

typedef struct s_env
{
	char			*data;
	int				unset_flag;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
	int				hd_file;
	int				error;
}	t_token;

typedef struct s_tokens
{
	t_token	*first_tok;
	t_token	**toks;
	int		tok_cnt;
	t_env	*env;
	char	**paths;
	int		initfd[2];
	int		cmd_cnt;
	int		prev_exit;
	int		error;
}	t_tokens;

typedef struct s_cmd
{
	struct s_cmd	*prev;
	char			**args;
	int				pipefd[2];
	int				redir_in_flg;
	int				redir_out_flg;
	int				pipe_done_flg;
	int				exit_code;
}	t_cmd;

//~~~~~~~~~~~~~~~~PARSER~~~~~~~~~~~~~~//
t_token		*new_token(char *value, int type);
t_token		*token_last(t_token *tok);
int			addback_token(t_token **tok, char *value, int type);
int			add_space(char *line, t_token **tok_first, int *i);
int			add_singquote(char *line, t_token **tok_first, int *i);
int			add_dblquote(char *line, t_token **tok_first, int *i);
int			add_specchar(char *line, t_token **tok_first, int *i);
int			add_str(char *line, t_token **tok_first, int *i);
int			is_specchar(char c);
void		print_error(int tok_char);
void		malloc_error(t_token **first_tok, t_tokens *tokens);
t_tokens	init_tokens(t_token **tok_first, t_env *new_env, int exit_code);
char		**lst_to_arr(t_token **exp_tok, t_env *env);
t_token		*parser(char *line);

//~~~~~~~~~~~~~~~~EXPANDER~~~~~~~~~~~~~~//
void		exp_str(t_tokens *tokens, t_token **exp_tok, int *i, int exp_type);
void		exp_pipe(t_tokens *tokens, t_token **exp_tok, int *i);
void		exp_in_out(t_tokens *tokens,
				t_token **exp_tok, int *i, int is_pipe);
void		exp_spec_char(t_tokens *tokens, t_token **exp_tok, int *i);
char		*exp_dbl_q(t_tokens *tokens, int *i);
t_tokens	init_exp_tokens(t_token **exp_tok, t_env *new_env, int exit_code);
char		*dol_malloc_err(t_tokens *tokens);
char		*find_env(char *str, size_t *j, t_tokens *tokens);
char		*exp_dollar(t_tokens *tokens, int *i);
t_token		*expander(t_tokens *tokens);
int			exp_error(t_tokens *pars_tokens, t_token **new_tok);
void		free_tok_env_exit(t_token **tok_first, t_env **env);

void		print_toklst(char *header, t_token *tok_first);

//~~~~~~~~~~~~~~~~EXECUTOR~~~~~~~~~~~~~~//
t_token		**tok_to_lst(t_token *tok, int tok_cnt);
int			args_cnt(t_tokens *tokens, int i);
t_cmd		*init_cmd(t_tokens *tokens, int i);
void		in_redir(t_tokens *tokens, t_cmd *cmd, int i);
void		out_redir(t_tokens *tokens, t_cmd *cmd, int i);
void		do_redir(t_tokens *tokens, t_cmd *cmd, int i);
void		pipe_redir(t_tokens *tokens, t_cmd *cmd, int i);
char		**get_paths(t_token **tok_first, char **env, int i, int j);
void		do_execve(t_tokens *tokens, t_cmd *cmd);
void		wait_process(t_cmd *cmd, pid_t pid, int cmd_cnt);
int			check_hd(t_tokens *tokens);
void		exit_error(char *arg, char *msg, t_tokens *tokens, t_cmd *cmd);
void		free_cmd(t_cmd **cmd);
void		free_tok(t_token **tok);
void		free_env(t_env **env);
void		free_paths(t_tokens *tokens);
void		free_tokens(t_tokens *tokens, int type);
void		free_lst(char **lst);
int			exec_cmd(t_tokens *tokens, pid_t *pid, t_cmd **cmd, int *is_first);
int			executor(t_tokens *tokens);

//~~~~~~~~~~~~~~~~BUILTINS~~~~~~~~~~~~~~//
int			check_blt(char *cmd);
void		ft_env(t_env *env);
int			env_cnt(t_env *env);
void		ft_export(char **line, t_env **env);
void		ft_unset(char **cmd, t_env **env);
int			mod_strcmp(char *cmd, char *env);
int			ft_pwd(void);
int			ft_cd(char **cmd, t_env *env);
int			ft_exit(char **cmd);
void		exec_blt(t_cmd *cmd_s, t_env *env);
void		ft_echo(char **cmd);
int			var_exist(char *cmd, t_env *env);

//~~~~~~~~~~~~~~~~ENVIROMENT~~~~~~~~~~~~~~//
t_env		*our_env(void);
char		*update_shlvl(char *str);
t_env		*dup_env(char **env_array);

//~~~~~~~~~~~~~~~~SIGNALS~~~~~~~~~~~~~~//
void		do_signals(int mode);
void		heredoc_handle(int sig, siginfo_t *data, void *non_used_data);
void		handle_sigint(int sig, siginfo_t *data, void *non_used_data);
void		do_sigign(int signum);

void		mini_loop(char *line, t_env *env);
int			new_exit(char *line, t_env *env, int prev_exit);

int	g_exit;

#endif
