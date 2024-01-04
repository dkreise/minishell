/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:14:32 by dkreise           #+#    #+#             */
/*   Updated: 2023/10/07 16:20:49 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char		digit;
	long int	divider;
	long int	nl;

	nl = n;
	divider = 1;
	if (nl < 0)
	{
		write(fd, "-", 1);
		nl = nl * (-1);
	}
	while (nl / divider >= 10)
	{
		divider *= 10;
	}
	while (divider > 0)
	{
		digit = nl / divider + 48;
		write(fd, &digit, 1);
		nl = nl % divider;
		divider = divider / 10;
	}
}
