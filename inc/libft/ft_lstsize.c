/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:16:56 by dkreise           #+#    #+#             */
/*   Updated: 2023/10/10 18:30:01 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	size;

	if (lst == NULL)
		size = 0;
	else
	{
		size = 1;
		while (lst->next != NULL)
		{
			size ++;
			lst = lst->next;
		}
	}
	return (size);
}
/*
int main(void)
{
	char s1[] = "hello";
	char s2[] = "world";
	t_list *l1 = ft_lstnew(s1);
	t_list *l2 = ft_lstnew(s2);
	l1->next = l2;
	printf("%i\n", ft_lstsize(l1));
	printf("%i\n", ft_lstsize((void *)0));
	return (0);
}*/
