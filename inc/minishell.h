/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:50:18 by rpliego           #+#    #+#             */
/*   Updated: 2024/01/03 18:26:55 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <libft.h>

// TYPE: 0:str, 1:space, 2:' ', 3:" ", 4:>,<,|,$
typedef struct s_token
{
	char			*value;
	int 			type;
	struct s_token	*next;
} t_token;
/*
typedef struct s_toklst
{
	t_token	*first;
} t_toklst;*/

t_token	*new_token(char *value, int type);
t_token	*token_last(t_token *tok);
void	addback_token(t_token **tok, char *value, int type);

#endif
