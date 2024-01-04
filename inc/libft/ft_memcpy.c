/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 10:52:17 by dkreise           #+#    #+#             */
/*   Updated: 2023/10/09 13:38:55 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*pdst;

	i = 0;
	pdst = dst;
	if (!dst && !src)
		return (dst);
	while (i < n)
	{
		pdst[i] = ((unsigned char *)src)[i];
		i ++;
	}
	return (dst);
}
/*
int main(void)
{
	char d[15] = "abcdefg";
	char *p = d;
	ft_memcpy(p + 3, p, 6);
	printf("%s\n", d);
	return (0);
}*/
