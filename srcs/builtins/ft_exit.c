/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:57:38 by rpliego           #+#    #+#             */
/*   Updated: 2024/01/31 14:03:47 by dkreise          ###   ########.fr       */
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

int	ft_exit(char **cmd)
{
	if (cmd[1] == NULL)
	{
		printf("exit\n");
		exit(0);
	}
	else if (cmd[2])
	{
		printf("exit: too many arguments\n");
		return (1);
	}	
	else if (is_numeric(cmd) == FALSE)
	{
		printf("exit: numeric argument required\n");
		exit(255);
	}
	else
	{
		printf("exit\n");
		exit(ft_atoi(cmd[1]));
	}
}