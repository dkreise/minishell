/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:24:48 by rpliego           #+#    #+#             */
/*   Updated: 2024/01/12 16:00:26 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_pwd(void)
{
	char buffer[1024];

	if (getcwd(buffer, sizeof(buffer)) != NULL)
        printf("%s\n", buffer);
    else //cambiar
	{
		printf("ERROR AL HACER PWD\n");
        exit(0);
	}
}