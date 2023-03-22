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


// void init_data(t_data *data, char **envp)
// {
// 	data->envp = copy_envp(data, envp);
// }


int main(int ac, char **av, char **envp)
{
	t_data	*data;
	char	*input;

	welcome(ac, av);
	data = malloc(sizeof(t_data));
	if (!data)
		return (printf("Error: malloc failure (main)"), 1);
	// init_data(data, envp);
	while (1)
	{
		input = get_prompt();

		free(input);
	}
	free (data);

	return (0);
}
