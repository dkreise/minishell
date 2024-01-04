/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:50:18 by rpliego           #+#    #+#             */
/*   Updated: 2024/01/04 15:24:45 by rpliego          ###   ########.fr       */
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

// TYPE: 0:str, 1:space, 2:' ', 3:" ", 4:>,<,|,$
typedef struct s_token
{
	char			*value;
	int 			type;
	struct s_token	*next;
} t_token;

typedef struct s_env
{
	char			*data;
	struct s_env	*next; 
} t_env;

t_token	*new_token(char *value, int type);
t_token	*token_last(t_token *tok);
void	addback_token(t_token **tok, char *value, int type);

#endif
