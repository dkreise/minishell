/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:05:32 by rpliego           #+#    #+#             */
/*   Updated: 2024/01/26 15:52:55 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	have_n_flag(char *str)
{
	int	i;

	i = 1;
	if (!str)
		return (FALSE);
	if (str[0] != '-')
		return (FALSE);
	while (str[i])
	{
		if (str[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	ft_echo(char **cmd)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (have_n_flag(cmd[i]) == TRUE && cmd[i]) //need to fix echo -n -n -n "something"
	{
		i++;
		n_flag = 1;
	}
	while (cmd[i] != NULL)
	{
		if (!cmd[i])
			break ;
		printf("%s", cmd[i]);
		i++;
		if (cmd[i])
			printf(" ");
	}
	if (n_flag == 0)
		printf("\n");
}
