/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:02:21 by dkreise           #+#    #+#             */
/*   Updated: 2023/10/09 13:24:19 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	i;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	i = 0;
	if (size <= len_dst)
		return (len_src + size);
	while (src[i] != '\0' && i < size - len_dst - 1)
	{
		dst[len_dst + i] = src[i];
		i ++;
	}
	dst[len_dst + i] = '\0';
	return (len_dst + len_src);
}
/*
int main(void)
{
    char d[20] = "hello";
    char s[] = "  world !";
    size_t n = 5;
    printf("%zu\n%s\n", ft_strlcat(d, s, n), d);
    return (0);
}*/
