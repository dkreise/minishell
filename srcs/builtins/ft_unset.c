/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 21:29:31 by rpliego           #+#    #+#             */
/*   Updated: 2024/01/14 20:06:00 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_unset(char **cmd, t_env **env)
{
	t_env	*aux;
	t_env	*first;
	int		i;

	i = 1;
	if (*env == NULL)
		return ;
	aux = *env;
	first = *env;
	while (cmd[i])
	{
		while (aux != NULL)
		{
			if (mod_strcmp(cmd[i], aux->data) == 1)
				aux->unset_flag = 1;
			aux = aux->next;
		}
		aux = first;
		i++;
	}
}

	// if (mod_strcmp(cmd[1], (*env)->data) == 1)
	// {
	// 	remove = *env;
	// 	*env = (*env)->next;
	// 	free(remove->data);
	// 	free(remove);
	// 	//printf("%s", (*env)->data);
	// 	return ;
	// }