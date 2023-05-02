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

int	here_doc(char *delimiter)
{
	char	*str;
	int		fd;

	fd = open("here_doc.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
	str = readline(">");
	while (ft_strncmp(str, delimiter, ft_strlen(delimiter))
		|| ft_strlen(delimiter) != ft_strlen(str))
	{
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
		str = readline(">");
	}
	free(str);
	close(fd);
}

void	outfile_handler(t_cmdGroup *group)
{
	t_outs	*outs;

	outs = group->outs;
	while (outs)
	{
		if (outs->append)
			group->outfile = open(outs->str, O_WRONLY | O_CREAT | O_APPEND, 0777);
		else
			group->outfile = open(outs->str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (group->outfile == -1)
		{
			perror("-bash: "); // exit status handling
			return ;
		}
		outs = outs->next;
	}
}

void	infile_handler(t_cmdGroup *group)
{
	t_ins	*ins;

	ins = group->ins;
	while (ins)
	{
		if (ins->heredoc)
		{
			here_doc(ins->str);
			group->infile = open("here_doc.txt", O_RDONLY);
		}
		else
			group->infile = open(ins->str, O_RDONLY);
		if (group->infile == -1)
		{
			perror("-bash: "); // exit status handling
			return ;
		}
		ins = ins->next;
	}
}

int	init_fds(t_data *data)
{
	t_cmdGroup *group;

	group = data->cmdGroup;
	while (group)
	{
		group->outfile = 1;
		if (group->ins)
			infile_handler(group);
		if (group->outs)
			outfile_handler(group);
		pipe(group->pipe);  // error check?
		group = group->next;
	}
}