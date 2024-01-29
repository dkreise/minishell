/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:24:48 by rpliego           #+#    #+#             */
/*   Updated: 2024/01/29 17:27:34 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd(void)
{
	char buffer[1024]; //look this

	if (getcwd(buffer, sizeof(buffer)) != NULL)
        printf("%s\n", buffer);
    else
	{
		ft_putstr_fd("ERROR AL HACER PWD\n", 2);
		return (1);
	}
	return (0);
}
