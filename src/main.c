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
	// data->raw_input = NULL;
	data->envp_ll = init_envp_ll(envp);
	// while (data->envp_ll)
	// {
	// 	printf("key: %s\n", data->envp_ll->envp_key);
	// 	printf("value: %s\n", data->envp_ll->envp_value);
	// 	data->envp_ll = data->envp_ll->next;
	// }
	init_envp_arr(data, envp);
	// int i = 0;
	// while (data->envp_arr[i])
	// {
	// 	printf("envp index %i: %s\n", i, data->envp_arr[i]);
	// 	i++;
	// }
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;
	char *input;

	welcome(ac, av);
	data = ft_calloc(1, sizeof(t_data)); //ft_calloc, malloc?
	// data = malloc(sizeof(t_data));
	if (!data)
		return (printf("Error: malloc failure (main)"), 1);
	init_data(data, envp);
	while (1)
	{
		input = readline(PROMPT);
		// data->raw_input = readline(PROMPT);
		// add_history(data->raw_input); // if (ft_strlen(data->raw_input) > 0)
		add_history(input); 
		input_handler(input);
		free(input); //needed??
	}
	free (data);
	return (0);
}
