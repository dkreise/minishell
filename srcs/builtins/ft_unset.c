/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 21:29:31 by rpliego           #+#    #+#             */
/*   Updated: 2024/01/10 20:16:19 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_unset(char **cmd, t_env **env)
{
	t_env	*aux;
	t_env	*remove;

	if (*env == NULL)
		return ;
	if (mod_strcmp(cmd[1], (*env)->data) == 1)
	{
		remove = *env;
		*env = (*env)->next;
		free(remove->data);
		free(remove);
		//printf("%s", (*env)->data);
		return ;
	}
	aux = *env;
	while (aux->next != NULL)
	{
		if (mod_strcmp(cmd[1], aux->next->data) == 1)
		{
			remove = aux->next;
			aux->next = aux->next->next;
			free(remove);
		}
		aux = aux->next;
	}
}