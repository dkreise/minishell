/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:20:38 by dkreise           #+#    #+#             */
/*   Updated: 2023/10/09 16:37:58 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*newstr;
	unsigned int	i;
	unsigned int	len;

	i = 0;
	len = ft_strlen(s);
	newstr = malloc((len + 1) * sizeof(char));
	if (newstr == NULL)
		return (0);
	while (i < len)
	{
		newstr[i] = f(i, s[i]);
		i ++;
	}
	newstr[i] = '\0';
	return (newstr);
}
/*
char ft_encrypt(unsigned int i, char c)
{
	return (c - i);
}

int main(void)
{
	printf("%s\n", ft_strmapi("hello", &ft_encrypt));
	return (0);
}*/
