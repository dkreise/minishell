/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:49:20 by dkreise           #+#    #+#             */
/*   Updated: 2023/10/10 18:36:37 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
/*
int main(void)
{
	char s1[] = "hello";
	char s2[] = "world";
	t_list *l = ft_lstnew(s1);
	t_list *new = ft_lstnew(s2);
	ft_lstadd_front(&l, new);
	printf("%s\n", new->next->content);
	return (0);
}*/
