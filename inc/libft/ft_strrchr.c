/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 11:29:40 by dkreise           #+#    #+#             */
/*   Updated: 2023/10/09 15:07:07 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = ft_strlen(s);
	while (len >= 0)
	{
		if (s[len] == (char)c)
			return ((char *)s + len);
		len --;
	}
	return (0);
}
/*
int main(void)
{
	char s[] = "";
	char c = 'a';
	printf("%s\n", ft_strrchr(s, c));
	return (0);
}*/
