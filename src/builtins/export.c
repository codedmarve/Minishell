/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moduwole <moduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 00:24:34 by moduwole          #+#    #+#             */
/*   Updated: 2023/03/29 00:24:34 by moduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	issmaller(char *str, char *str2)
{
	int i;

	i = 0;
	if (!str2)
		return (1);
	while (str[i] && str2[i])
	{
		if (str[i] < str2[i])
			return (1);
		else if (str[i] > str2[i])
			return (0);
		i++;
	}
	if (str[i] && !str2[i])
		return (0);
	return (1);
}

t_envp *set_min(t_data *data)
{
	t_envp *tmp;

	tmp = data->henv;
	while (tmp)
	{
		if (!tmp->sorted)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	export_print(t_data *data)
{
	t_envp *tmp;
	t_envp *tmp2;
	t_envp *min;

	tmp = data->henv;
	while (tmp)
	{
		tmp2 = data->henv;
		min = set_min(data);
		while (tmp2)
		{
			if (!issmaller(min->envp_key, tmp2->envp_key)
				&& !tmp2->sorted)
				min = tmp2;
			tmp2 = tmp2->next;
		}
		min->sorted = 1;
		printf("declare -X %s=", min->envp_key);
		printf("\"%s\"\n", min->envp_value);
		tmp = tmp->next;
	}
}

int	is_update(t_data *data, char *key, char *value)
{
	t_envp	*ptr;

	ptr = data->henv;
	while (ptr)
	{
		if (!ft_strncmp(ptr->envp_key, key, ft_strlen(key))
			&& ft_strlen(ptr->envp_key) == ft_strlen(key))
		{
			if (ft_strncmp(ptr->envp_value, value, ft_strlen(value))
				|| ft_strlen(ptr->envp_value) != ft_strlen(value))
			{
				free(ptr->envp_value);
				ptr->envp_value = ft_strdup1(value);
			}
			return (1);
		}
		ptr = ptr->next;
	}
	return (0);
}

void	export(t_data *data, char *var)
{
	char	**str;
	char	*ptr;
	char	*tmp;

	ptr = ft_strchr(var, '=');
	if (!ptr)
		return ;
	tmp = ft_strdup2(var, ptr - var);
	str = ft_split(var, '\0');
	if (!is_update(data, tmp, ptr + 1))
		envplist_handler(&data->henv, str);
	free(tmp);
	ft_clarr(str);
}