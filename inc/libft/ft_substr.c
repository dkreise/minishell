/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:15:15 by dkreise           #+#    #+#             */
/*   Updated: 2023/10/09 16:13:46 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	substr = (char *) malloc((len + 1) * sizeof(char));
	if (substr == NULL)
		return (0);
	i = 0;
	while (i < len && s[start + i] != '\0')
	{
		substr[i] = s[start + i];
		i ++;
	}
	substr[len] = '\0';
	return (substr);
}
/*
int main(void)
{
	char *res;
	
	res = ft_substr("vnsdr irof lj", 20, 5);
	printf("%s\n", res);
	return (0);
}*/
