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

void	init_list(t_data *data, char **envp)
{
	data->henv = NULL;
	envplist_handler(&data->henv, envp);


	print_env(data);
	printf("\n\n");

	export(data, "CODED=marvellous");
	print_env(data);
	printf("\n\n");

	// unset(data, "CODED");
	unset(data, "PATH=");

	printf("\n\n");
	print_env(data);
	// export_print(data);
	
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	(void)envp;
	welcome(ac, av);

	data = ft_calloc(1, sizeof(t_data)); //ft_calloc, malloc?
	if (!data)
		return (printf("Error: malloc failure (main)"), 1);
	init_list(data, envp);
	// while (1)
	for (int i = 0; i < 1; i++)
	{
		data->input = readline(PROMPT);
		add_history(data->input); // if (ft_strlen(data->raw_input) > 0)
		// input_handler(data, data->input);
		free(data->input);
	}
	free(data);
	return (0);
}
