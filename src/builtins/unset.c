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

void	ft_unset(t_data *data, char **key)
{
	t_envp *ptr;
	t_envp *ptr2;

	ptr = data->env_lst;
	if (!ft_strncmp(ptr->envp_key, key[1], ft_strlen(key[1]))
		&& ft_strlen(ptr->envp_key) == ft_strlen(key[1]))
	{
		data->env_lst = ptr->next;
		free(ptr->envp_key);
		free(ptr->envp_value);
		free(ptr);
		return ;
	}
	while (ptr->next)
	{
		ptr2 = ptr->next;
		if (!ft_strncmp(ptr2->envp_key, key[1], ft_strlen(key[1]))
			&& ft_strlen(ptr2->envp_key) == ft_strlen(key[1]))
		{
			ptr->next = ptr2->next;
			free(ptr2->envp_key);
			free(ptr2->envp_value);
			free(ptr2);
			return ;
		}
		ptr = ptr->next;
	}
}
