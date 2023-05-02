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
	unlink("here_doc.txt");
	free(data->input);
	free_token_lst(&data->token_lst);
	free_cmdGroup(data);
}


void	in_out_handler(t_cmdGroup *group)
{
	if (group->infile == -1 || group->outfile == -1 || !group->cmd)
	{
		if (!isbuiltin(group))
			exit(1);
		return ;
	}
	if (!isbuiltin(group))
		close(group->pipe[0]);
	if (group->next && group->outfile == 1)
		dup2(group->pipe[1], STDOUT_FILENO);
	if (group->outfile > 1)
	{
		dup2(group->outfile, STDOUT_FILENO);
		close(group->outfile);
	}
	close(group->pipe[1]);
	if (group->prev && group->prev->outfile == 1
		&& group->infile == 0)
	{
		close(group->prev->pipe[1]);
		dup2(group->prev->pipe[0], STDIN_FILENO);
		close(group->prev->pipe[0]);
	}
	if (group->infile > 0)
		dup2(group->infile, STDIN_FILENO);
}

void pclose_pipes(t_cmdGroup *group)
{
	if (group->prev)
	{
		close(group->prev->pipe[0]);
		close(group->prev->pipe[1]);
	}
}

void	parent_wait(t_cmdGroup *group)
{
	t_cmdGroup *tmp;

	tmp = group;
	while (tmp)
	{
		waitpid(tmp->pid, NULL, 0);
		tmp = tmp->next;
	}
}

int	execute(t_data *data)
{
	t_cmdGroup *group;
	int stdin;
	int stdout;

	group = data->cmdGroup;
	while (group)
	{
		if (isbuiltin(group))
		{
			stdin = dup(STDIN_FILENO);
			stdout = dup(STDOUT_FILENO);
			in_out_handler(group);
			builtin(data, group);
		}
		else
		{
			group->pid = fork();
			if (group->pid == 0)
			{
				in_out_handler(group);
				// to do exit status
				if (execve(group->cmd[0], group->cmd, NULL) == -1)
					perror("-bash: ");
				exit(1);
			}
		}
		if (isbuiltin(group))
		{
			dup2(stdin, STDIN_FILENO);
			dup2(stdout, STDOUT_FILENO);
			close(stdin);
			close(stdout);
		}
		else
			pclose_pipes(group);
		group = group->next;
	}
	parent_wait(data->cmdGroup);
}