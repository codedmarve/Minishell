/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moduwole <moduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:40:35 by moduwole          #+#    #+#             */
/*   Updated: 2023/04/05 14:40:35 by moduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void unset_free(t_envp *ptr)
{
	free(ptr->key);
	free(ptr->value);
	free(ptr);
}

void	ft_unset(t_data *data, char **key)
{
	t_envp *ptr;
	t_envp *ptr2;

	ptr = data->env_lst;
	g_exit_status = 0;
	if (!ft_strncmp(ptr->key, key[1], ft_strlen(key[1]))
		&& ft_strlen(ptr->key) == ft_strlen(key[1]))
	{
		data->env_lst = ptr->next;
		unset_free(ptr);
		return ;
	}
	while (ptr->next)
	{
		ptr2 = ptr->next;
		if (!ft_strncmp(ptr2->key, key[1], ft_strlen(key[1]))
			&& ft_strlen(ptr2->key) == ft_strlen(key[1]))
		{
			ptr->next = ptr2->next;
			unset_free(ptr2);
			return ;
		}
		ptr = ptr->next;
	}
}
