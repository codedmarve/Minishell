/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moduwole <moduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:25:47 by moduwole          #+#    #+#             */
/*   Updated: 2023/03/09 13:25:47 by moduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_data(t_data *data, char **envp)
{
	data->input = NULL;
	data->envp_ll = NULL;
	// data->envp_ll = init_envp_ll(envp);
	data->input_pipe_groups = NULL;
	data->token_ll = NULL;
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	welcome(ac, av);
	data = malloc(sizeof(t_data)); 
	if (!data)
		return (printf("Error: malloc failure (main)"), 1);
	init_data(data, envp);
	while (1)
	{
		data->input = readline(PROMPT);
		add_history(data->input); // if (ft_strlen(data->input) > 0)
		input_handler(data);
	}
	free (data);
	return (0);
}
