/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 22:11:05 by rpliego           #+#    #+#             */
/*   Updated: 2024/01/29 18:25:38 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_correct(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=' )
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void	ft_env(t_env *env)
{
	while (env)
	{
		if (is_correct(env->data) == TRUE && env->unset_flag == FALSE)
			printf("%s\n", env->data);
		env = env->next;
	}
}
