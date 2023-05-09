/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moduwole <moduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 09:37:41 by moduwole          #+#    #+#             */
/*   Updated: 2023/04/29 09:37:41 by moduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_data *data, char **str)
{
	t_envp *tmp;

	if (arrlen(str) > 1)
	{
		printf("env: '%s': No such file or directory\n", str[1]);
		g_exit_status = 0;
		return ;
	}
	tmp = data->env_lst;
	while (tmp)
	{
		printf("%s=", tmp->envp_key);
		printf("%s\n", tmp->envp_value);
		tmp = tmp->next;
	}
	g_exit_status = 0;
}
