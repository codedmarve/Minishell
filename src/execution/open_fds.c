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

void ctrl_c_heredoc_parent(int sig)
{
	(void)sig;
}

void	sig_parent_heredoc2(void)
{
	struct sigaction	sa;

	ignore_ctrl_bslash();
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = ctrl_c_heredoc_parent;
	sigaction(SIGINT, &sa, NULL);
}

int here_doc2(char *delimeter)
{
	char	*str;
	int		fd;

	fd = open("here_doc.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
	str = readline(">");
	while (ft_strncmp(str, delimeter, ft_strlen(delimeter))
		|| ft_strlen(delimeter) != ft_strlen(str))
	{
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
		str = readline(">");
	}
	free(str);
	close(fd);
	exit(1);
}

int	here_doc(char *delimeter)
{
	int		pid;
	int		chexit;

	chexit = 1;
	pid = fork();
	if (pid == 0)
	{
		sig_heredoc();
		here_doc2(delimeter);
	}
	else
	{
		sig_parent_heredoc2();
		//sig_parent_heredoc();
		//sig_interactive();
		//sig_noninteractive();
		waitpid(pid, &chexit, 0);
		if (WIFEXITED(chexit))
			return (1);
	}
	return (0);
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

int	infile_handler(t_cmdGroup *group)
{
	t_ins	*ins;

	ins = group->ins;
	while (ins)
	{
		if (ins->heredoc)
		{
			if (!here_doc(ins->str))
				return (0);
			group->infile = open("here_doc.txt", O_RDONLY);
		}
		else
			group->infile = open(ins->str, O_RDONLY);
		if (group->infile == -1)
		{
			perror("-bash: "); // exit status handling
			return (1);
		}
		ins = ins->next;
	}
	return (1);
}

int	init_fds(t_data *data)
{
	t_cmdGroup *group;

	group = data->cmdGroup;
	while (group)
	{
		group->outfile = 1;
		if (group->ins)
			if (!infile_handler(group))
				return (0);
		if (group->outs)
			outfile_handler(group);
		pipe(group->pipe);  // error check?
		group = group->next;
	}
	return (1);
}