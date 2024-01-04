/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:07:44 by dkreise           #+#    #+#             */
/*   Updated: 2023/10/10 12:41:24 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	ft_lennum(long int n)
{
	long int	nl;
	long int	len;

	nl = n;
	len = 0;
	if (nl <= 0)
	{
		len ++;
		nl *= (-1);
	}
	while (nl > 0)
	{
		len ++;
		nl /= 10;
	}
	return (len);
}

static int	ft_div(long int n)
{
	int	divider;

	divider = 1;
	while (n / divider >= 10)
		divider *= 10;
	return (divider);
}

char	*ft_itoa(int n)
{
	char		*str;
	long int	divider;
	long int	nl;

	nl = n;
	str = malloc((ft_lennum(n) + 1) * sizeof(char));
	if (str == NULL)
		return (0);
	if (nl < 0)
	{
		*str = '-';
		nl *= (-1);
		str ++;
	}
	divider = ft_div(nl);
	while (divider > 0)
	{
		*str = (nl / divider) + '0';
		nl = nl % divider;
		divider /= 10;
		str ++;
	}
	*str = '\0';
	return (str - ft_lennum(n));
}
/*
int main(void)
{
	int n = -86075843;
	printf("%i\n", n);
	printf("%s\n", ft_itoa(n));
	return (0);
}*/
