/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 22:49:57 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/04/04 17:59:52 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	str_counter(char *input, char delimiter)
{
	int		i;
	int		counter;

	i = 0;
	counter = 0;
	while (input[i])
	{
		if (input[i + 1] == '\0')
		{
			counter++;
			break ;
		}
		if (!quotes_are_closed(input[i]))
		{
			i++;
			continue ;
		}
		if (input[i] == delimiter)
		{
			counter++;
		}
		i++;
	}
	return (quotes_default(), counter);
}

char	*init_str(char *input, char delimiter)
{
	int		strlen;
	char	*str;

	strlen = 0;
	while (input[strlen])
	{
		if (quotes_are_closed(input[strlen]) && input[strlen] == delimiter)
			break ;
		strlen++;
	}
	if (!strlen)
	{
		return (quotes_default(), NULL);
	}
	str = ft_calloc(strlen + 1, sizeof(char));
	str = ft_memcpy(str, input, strlen);
	return (quotes_default(), str);
}

char	**shell_split(char *input, char delimiter)
{
	int		i;
	int		substr_idx;
	char	**splitted;

	if (!input)
		return (NULL);
	splitted = ft_calloc(str_counter(input, delimiter), sizeof(char *));
	if (!splitted)
		return (NULL);
	i = -1;
	substr_idx = 0;
	while (input[++i])
	{
		if (substr_idx && !quotes_are_closed(input[i - 1]))
			continue ;
		if (!substr_idx || input[i - 1] == delimiter)
		{
			if (init_str(input + i, delimiter))
			{
				splitted[substr_idx++] = init_str(input + i, delimiter);
				// printf("substr idx: %d, str: %s\n", substr_idx - 1,  splitted[substr_idx - 1]);
			}
		}
	}
	splitted[substr_idx] = NULL;
	// i = 0;
	// while (splitted[i])
	// 	{
	// 		printf("substr idx: %d, str: %s\n", i,  splitted[i]);
	// 		i++;
	// 	}
	return (quotes_default(), splitted);
}

char	**shell_split_remove_spaces(char *input)
{
	char	**splitted;
	int		i;

	splitted = shell_split(input, '|');
	i = -1;
	while (splitted[++i])
		splitted[i] = ft_strtrim(splitted[i], " \f\r\t\n\v");
	return (splitted);
}
