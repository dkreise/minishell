/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:32:28 by dkreise           #+#    #+#             */
/*   Updated: 2024/01/09 19:28:48 by dkreise          ###   ########.fr       */
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

static void	free_params(char *s1, char *s2, int aux)
{
	if (aux == FIRST || aux == BOTH)
		free(s1);
	else if (aux == SECOND || aux == BOTH)
		free(s2);
}

char	*ft_strjoin(char const *s1, char const *s2, int aux)
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
	free_params((char *)s1, (char *)s2, aux);
	return (strjoin - len_s1 - len_s2);
}
