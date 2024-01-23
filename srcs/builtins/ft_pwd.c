/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:24:48 by rpliego           #+#    #+#             */
/*   Updated: 2024/01/23 21:56:58 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd(void)
{
	char buffer[1024];

	if (getcwd(buffer, sizeof(buffer)) != NULL)
        printf("%s\n", buffer);
    else
	{
		printf("ERROR AL HACER PWD\n");
		return (1);
	}
	return (0);
}