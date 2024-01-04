/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 12:47:29 by dkreise           #+#    #+#             */
/*   Updated: 2023/10/09 12:03:25 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	uc;

	i = 0;
	ptr = (unsigned char *)s;
	uc = c;
	while (i < n)
	{
		if (ptr[i] == uc)
			return (&ptr[i]);
		i ++;
	}
	return (0);
}
/*
int main(void)
{
	printf("%c\n", *((char*)ft_memchr("majfjan", 'a', 6)));
	return (0);
}*/
