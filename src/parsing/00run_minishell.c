/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00run_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:00:25 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/05/10 11:46:00 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	run_minishell(t_data *data)
{
	if (!ft_strncmp(data->input, "exit", 4) && ft_strlen(data->input) == 4)
		exit_free(data);
	if (early_err(data) == -1)
	{
		g_exit_status = 2;
		return (-1);
	}
	parser(data);
	cmd_init(data);
	get_cmdpath(data);
	if (!init_fds(data))
		return (exec_free(data), 0);
	execute(data);
	exec_free(data);
	return (1);
}
