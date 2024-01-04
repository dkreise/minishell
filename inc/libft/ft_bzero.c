/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:38:54 by dkreise           #+#    #+#             */
/*   Updated: 2023/10/08 18:42:20 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = s;
	while (i < n)
	{
		ptr[i] = '\0';
		i ++;
	}
}
/*
// doesn't work printf("%s\n", s);
int main(void)
{
	unsigned char s[10] = "npjvorkla";
	ft_bzero(s, 3);
	printf("%c\n", s[1]);
	return (0);
}*/
