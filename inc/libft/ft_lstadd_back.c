/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:43:53 by dkreise           #+#    #+#             */
/*   Updated: 2023/10/11 14:36:45 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (*lst == NULL)
		ft_lstadd_front(lst, new);
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
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
	ft_lstadd_back(&l1, l3);
	t_list *last = ft_lstlast(l1);
	printf("%s\n", last->content);
	return (0);
}*/
