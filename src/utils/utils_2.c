/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moduwole <moduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:23:10 by moduwole          #+#    #+#             */
/*   Updated: 2023/03/27 14:23:10 by moduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strdup2(const char *str, int len)
{
	char	*dup;
	int		i;

	i = 0;
	dup = ft_calloc(len + 1, sizeof(char));
	if (dup == NULL)
		return (NULL);
	while (i < len)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strdup1(const char *str)
{
	char	*dup;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(str) + 1;
	dup = malloc(len * sizeof(char));
	if (dup == NULL)
		return (NULL);
	while (str[i] && str[i] != ' ')
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	print_env(t_data *data)
{
	t_envp *tmp;

	tmp = data->henv;
	while (tmp)
	{
		printf("%s=", tmp->envp_key);
		printf("%s\n", tmp->envp_value);
		tmp = tmp->next;
	}
}

// int isbuiltin(t_data *data)
// {
	
// }