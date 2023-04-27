/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moduwole <moduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:00:43 by moduwole          #+#    #+#             */
/*   Updated: 2023/04/25 15:00:43 by moduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_cmdGroup(t_data *data)
{
	t_cmdGroup *tmp = data->cmdGroup;
	while (tmp)
	{
		if (tmp->cmd)
			ft_clarr(tmp->cmd);

		if (tmp->ins)
		{
			t_ins *ptr = tmp->ins;
			while (tmp->ins)
			{
				free(ptr->str);
				tmp->ins = ptr->next;
				free(ptr);
				ptr = tmp->ins;
			}
		}
		if (tmp->outs)
		{
			t_outs *ptr = tmp->outs;
			while (tmp->outs)
			{
				free(ptr->str);
				tmp->outs = ptr->next;
				free(ptr);
				ptr = tmp->outs;
			}
		}
		if (tmp->str)
			free(tmp->str);

		data->cmdGroup = tmp->next;
		free(tmp);
		tmp = data->cmdGroup;
	}
}

void	free_all(t_data *data)
{
	free(data->input);
	free_token_lst(&data->token_lst);
	free_cmdGroup(data);
}

int	execute(t_data *data)
{
	t_cmdGroup *group;

	group = data->cmdGroup;
	int i = 1;
	while (group)
	{
		group->pid = fork();

		if (group->pid == 0)
		{
//			sig_noninteractive();
			// if (group->infile != 0)
			// {
			// 	// if (group->)
			// 	dup2(group->infile, STDIN_FILENO);
			// }


			if (group->prev && group->prev->outfile == 1)
			{
				// close(group->prev->pipe[1]);
				dup2(group->prev->pipe[0], STDIN_FILENO);
			}



			if (group->next && group->outfile == 1)
			{
				// close(group->pipe[0]);
				dup2(group->pipe[1], STDOUT_FILENO);
			}

			// printf("group %i\n", i);=

			// to do exit status
			if (execve(group->cmd[0], group->cmd, NULL) == -1)
			{
				perror("-bash: ");
				exit(1);
			}
		}
		i++;
		group = group->next;
	}

	group = data->cmdGroup;
	while (group)
	{
		waitpid(group->pid, NULL, 0);
		group = group->next;
	}
//	sig_interactive();
}