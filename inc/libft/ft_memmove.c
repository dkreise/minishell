/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 11:16:04 by dkreise           #+#    #+#             */
/*   Updated: 2023/10/08 16:23:12 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*pdst;
	unsigned char	*psrc;

	i = 0;
	pdst = (unsigned char *)dst;
	psrc = (unsigned char *)src;
	if (psrc > pdst)
	{
		while (i < len)
		{
			pdst[i] = psrc[i];
			i ++;
		}
	}
	else if (psrc < pdst)
	{
		while (i < len)
		{
			pdst[len - 1 - i] = psrc[len - 1 - i];
			i ++;
		}
	}
	return (dst);
}
/*
int main(void)
{
	char s[] = "fmvsvvpworj";
	ft_memmove(s + 3, s, 8);
	printf("%s\n", s);
	return (0);
}*/
