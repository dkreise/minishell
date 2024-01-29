/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:05:32 by rpliego           #+#    #+#             */
/*   Updated: 2024/01/29 18:25:30 by rpliego          ###   ########.fr       */
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
	if (!str[1])
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
	while (have_n_flag(cmd[i]) == TRUE && cmd[i])
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
