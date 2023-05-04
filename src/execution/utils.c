/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moduwole <moduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:32:12 by moduwole          #+#    #+#             */
/*   Updated: 2023/05/03 10:32:12 by moduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pclose_pipes(t_cmdGroup *group)
{
	if (group->prev)
	{
		close(group->prev->pipe[0]);
		close(group->prev->pipe[1]);
	}
}

void	parent_wait(t_cmdGroup *group)
{
	t_cmdGroup	*tmp;

	tmp = group;
	while (tmp)
	{
		waitpid(tmp->pid, NULL, 0);
		tmp = tmp->next;
	}
}

void	ft_default(int stdin, int stdout)
{
	dup2(stdin, STDIN_FILENO);
	dup2(stdout, STDOUT_FILENO);
	close(stdin);
	close(stdout);
}
