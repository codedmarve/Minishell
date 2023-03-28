/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moduwole <moduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:25:53 by moduwole          #+#    #+#             */
/*   Updated: 2023/03/22 16:25:53 by moduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	arrlen(char **arr)
{
	int	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	init_null(t_data *data)
{
	data->path = NULL;
	data->cmd = NULL;
	data->env = NULL;
	data->prenv = NULL;
}

void	ft_clarr(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	ft_clear(t_data *data)
{
	ft_clarr(data->cmd);
	ft_clarr(data->prenv);
	ft_clarr(data->env);
}

int	is_simple(char *str)
{
	int i;
	int c;

	i = 0;
	while (str[i])
	{
		c = str[i];
		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
			|| c == ' ' || c == '-' || c == '/' || c == '>')
				i++;
		else
			return (0);
	}
	return (1);
}
