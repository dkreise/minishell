/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:57:38 by rpliego           #+#    #+#             */
/*   Updated: 2024/02/04 17:54:40 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_numeric(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[1][i])
	{
		if (str[1][i] >= '0' && str[1][i] <= '9')
			j++;
		i++;
	}
	if (i == j)
		return (TRUE);
	return (FALSE);
}

int	ft_exit(char **cmd, int prev_exit)
{
	if (cmd[1] == NULL)
	{
		ft_putstr_fd("exit\n", 2);
		exit(prev_exit);
	}
	else if (cmd[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	else if (is_numeric(cmd) == FALSE)
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		exit(255);
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
		exit(ft_atoi(cmd[1]));
	}
}
