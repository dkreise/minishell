/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:38:16 by dkreise           #+#    #+#             */
/*   Updated: 2023/10/09 16:57:02 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;
	unsigned int	len;

	i = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		f(i, &s[i]);
		i ++;
	}
}
/*
void	ft_encrypt(unsigned int i, char *c)
{
	*c = *c - i;
}

int main(void)
{
	char	s[] = "hello";
	ft_striteri(s, &ft_encrypt);
	printf("%s\n", s);
	return (0);
}*/
