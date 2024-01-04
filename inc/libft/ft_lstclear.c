/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:17:31 by dkreise           #+#    #+#             */
/*   Updated: 2023/10/11 15:37:31 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cur;
	t_list	*lnext;

	lnext = *lst;
	while (lnext != NULL)
	{
		cur = lnext;
		lnext = lnext->next;
		del(cur->content);
		free(cur);
	}
	*lst = NULL;
}
