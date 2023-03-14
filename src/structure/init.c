/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moduwole <moduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 19:42:52 by moduwole          #+#    #+#             */
/*   Updated: 2023/03/13 19:42:52 by moduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_null(t_data *data, char *pwd)
{
	data->i = 0;
	data->prompt = NULL;
	data->line = NULL;
	data->tmp = NULL;
	ft_bzero(pwd, 1000);
}
