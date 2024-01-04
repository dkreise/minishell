/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:32:28 by dkreise           #+#    #+#             */
/*   Updated: 2023/10/07 17:14:48 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	fill(size_t len, char const *s, char **strjoin)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		**strjoin = s[i];
		*strjoin = *strjoin + 1;
		i ++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*strjoin;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	strjoin = (char *) malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (strjoin == NULL)
		return (0);
	fill(len_s1, s1, &strjoin);
	fill(len_s2, s2, &strjoin);
	*strjoin = '\0';
	return (strjoin - len_s1 - len_s2);
}
/*
int	main(void)
{
	char *res;
	res = ft_strjoin("hello ", "world!");
	printf("%s\n", res);
	return (0);
}*/
