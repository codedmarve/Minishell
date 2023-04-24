/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moduwole <moduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:34:57 by moduwole          #+#    #+#             */
/*   Updated: 2023/04/24 16:34:57 by moduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	infile_handler(group)
{
	t_ins	*infile;

	infile = group->ins;
	while (infile)
	{
		if (infile->heredoc)
			
	}
}

int	execute(t_data *data)
{
	t_cmdGroup *group;

	group = data->cmdGroup;
	if (group->ins)
	{
		while (group->)
	}
}