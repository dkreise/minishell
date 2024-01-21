/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:05:32 by rpliego           #+#    #+#             */
/*   Updated: 2024/01/20 19:52:28 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	has_n_flag(char *str)
{
	int	i;

	i = 1;
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
	while (cmd[i] != NULL)
	{
		if (has_n_flag(cmd[1]) == TRUE && n_flag == 0)
		{
			i += 1;
			n_flag = 1;
		}
		printf("%s", cmd[i]);
		i++;
		if (cmd[i])
			printf(" ");
	}
	if (n_flag == 0)
		printf("\n");
}
