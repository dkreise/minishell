/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:22:01 by dkreise           #+#    #+#             */
/*   Updated: 2023/10/09 16:12:45 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		if (haystack[i] == needle[0])
		{
			j = 0;
			while (needle[j] != '\0' && haystack[i + j] == needle[j]
				&& (i + j) < len)
				j ++;
			if (needle[j] == '\0')
				return (&((char *)haystack)[i]);
		}
		i ++;
	}
	return (0);
}
/*
int	main(void)
{
	char s1[] = "hello world";
	char s2[] = "lo";
	char *res;

	res = ft_strnstr(s1, s2, 7);
	printf("%s\n", res);
	return (0);
}*/
