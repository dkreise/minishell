/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:14:24 by dkreise           #+#    #+#             */
/*   Updated: 2023/10/09 15:07:31 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	c = (char)c;
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *)s);
		s ++;
	}
	if (c == '\0')
		return ((char *)s);
	return (0);
}
/*
int main(void)
{
    char s[] = "abcdssba";
    char c = '.';
    char *p = ft_strchr(s, c);
	printf("%s\n", p);
    return (0);
}*/
