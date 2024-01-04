/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:28:46 by dkreise           #+#    #+#             */
/*   Updated: 2023/10/11 12:43:08 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last;

	last = lst;
	if (lst == NULL)
		return (0);
	while (lst->next != NULL)
	{
		lst = lst->next;
		last = lst;
	}
	return (last);
}
/*
int main(void)
{
	char s1[] = "hello";
	char s2[] = "world";
	char s3[] = "!!!";
	t_list *l1 = ft_lstnew(s1);
	t_list *l2 = ft_lstnew(s2);
	t_list *l3 = ft_lstnew(s3);
	l1->next = l2;
	l2->next = l3;
	t_list *last = ft_lstlast(l1);
	printf("%s\n", last->content);
	return (0);
}*/
