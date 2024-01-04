/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:21:45 by dkreise           #+#    #+#             */
/*   Updated: 2023/10/07 16:31:06 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	int		len;
	int		i;

	len = ft_strlen(s1);
	dup = (char *) malloc(len + 1);
	if (dup == NULL)
		return (0);
	i = 0;
	while (i < len)
	{
		dup[i] = s1[i];
		i ++;
	}
	dup[len] = '\0';
	return (dup);
}
/*
int main(void)
{
	char s[] = "mfhjm!!! d";
	char *d;

	d = ft_strdup(s);
	printf("%s\n", d);
	return (0);
}*/
