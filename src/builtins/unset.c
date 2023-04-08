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

void	unset(t_data *data, char *key)
{
	t_envp *ptr;
	t_envp *ptr2;

	ptr = data->henv;
	if (!ft_strncmp(ptr->envp_key, key, ft_strlen(key))
		&& ft_strlen(ptr->envp_key) == ft_strlen(key))
	{
		data->henv = ptr->next;
		free(ptr);
		return ;
	}
	while (ptr->next)
	{
		ptr2 = ptr->next;
		if (!ft_strncmp(ptr2->envp_key, key, ft_strlen(key))
			&& ft_strlen(ptr2->envp_key) == ft_strlen(key))
		{
			ptr->next = ptr2->next;
			free(ptr2);
			return ;
		}
		ptr = ptr->next;
	}
}