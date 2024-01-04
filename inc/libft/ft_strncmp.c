/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strncmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:42:33 by dkreise           #+#    #+#             */
/*   Updated: 2023/10/09 16:12:13 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (*ptr1 != '\0' && *ptr2 != '\0' && i < n - 1)
	{
		if (*ptr1 != *ptr2)
			return (*ptr1 - *ptr2);
		ptr1 ++;
		ptr2 ++;
		i ++;
	}
	return (*ptr1 - *ptr2);
}
/*
int main(void)
{
	const char s1[] = "test\200";
	const char s2[] = "test\0";
	size_t n = 6;
	printf("%i\n", '\200');
	printf("%i\n", ft_strncmp(s1, s2, n));
	return (0);
}*/
