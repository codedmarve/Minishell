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
#include <string.h>

int main(int argc, char *argv[], char *env[])
{
	t_data	*data;

	welcome(argc, argv);
		
	data = malloc(sizeof(t_data));
	get_prompt(env, data);


	while (1)
		ft_readline(data);

	free(data->prompt);
	free(data);

	
	return 0;
}
