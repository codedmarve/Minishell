/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_t.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moduwole <moduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:24:34 by moduwole          #+#    #+#             */
/*   Updated: 2023/03/22 14:24:34 by moduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_path(t_data *data)
{
	int		i;
	char	**dst;

	dst = ft_calloc(arrlen(data->cmd) + 2, sizeof(char *));
	dst[0] = ft_strdup(data->path);
	i = 1;
	while (data->cmd[i])
	{
		dst[i] = ft_strdup(data->cmd[i]);
		i++;
	}
	ft_clarr(data->cmd);
	data->cmd = dst;
}

int	get_path(t_data *data)
{
	data->env = ft_calloc(arrlen(data->prenv) + 1, sizeof(char *));
	data->i = 0;
	while (data->i < arrlen(data->prenv))
	{
		if (data->prenv[data->i][ft_strlen(data->prenv[data->i]) - 1] != '/')
		{
			data->env[data->i] = ft_strjoin(data->prenv[data->i],
					data->tmp = ft_strjoin("/", data->cmd[0]));
			free(data->tmp);
		}
		else
			data->env[data->i] = ft_strjoin(data->prenv[data->i], data->cmd[0]);
		if (access(data->env[data->i], X_OK) == 0)
		{
			data->path = data->env[data->i];
			break ;
		}
		data->i++;
	}
	if (data->path)
		return (add_path(data), 1);
	return (perror("Error:"), 0);
}

void	execute(t_data *data)
{
	if (fork() == 0)
	{
		if (execve(data->cmd[0], data->cmd, NULL) == -1)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
		ft_clear(data);
	}
}

int simple_t(t_data *data)
{
	
	init_null(data);
	if (is_simple(data->input))
	{
		data->tmp = getenv("PATH");
		data->prenv = ft_split(data->tmp, ':');
		data->cmd = ft_split(data->input, ' ');
		if (access(data->cmd[0], X_OK) == 0)
			execute(data);
		else if (get_path(data))
			execute(data);
		else
			ft_clear(data);
	}
	return (1);
}