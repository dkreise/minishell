/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:58:39 by dkreise           #+#    #+#             */
/*   Updated: 2023/10/09 18:05:13 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isinset(char c, char const *set)
{
	while (*set != '\0')
	{
		if (c == *set)
			return (1);
		set ++;
	}
	return (0);
}

static char	*ft_fillstr(char *trimmed, int len, char *str)
{
	char	*tptr;
	int		i;

	i = 0;
	tptr = trimmed;
	while (i < len)
	{
		tptr[i] = str[i];
		i ++;
	}
	tptr[i] = '\0';
	return (trimmed);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	int		len_new;
	int		len_s1;
	int		i;
	char	*ptr;

	len_new = 0;
	len_s1 = ft_strlen(s1);
	i = 0;
	while (ft_isinset(s1[i], set) && s1[i] != '\0')
		i ++;
	ptr = (char *)&s1[i];
	if (s1[i] != '\0')
	{
		while (ft_isinset(s1[len_s1 - 1], set))
			len_s1 --;
		len_new = len_s1 - i;
		trimmed = malloc((len_new + 1) * sizeof(char));
		if (trimmed == NULL)
			return (0);
		trimmed = ft_fillstr(trimmed, len_new, ptr);
		return (trimmed);
	}
	return (ft_strdup(""));
}
/*
int main(void)
{
	char *new;
	new = ft_strtrim("  , hello world!.", ",. ");
	printf("%s\n", new);
	return (0);
}*/
