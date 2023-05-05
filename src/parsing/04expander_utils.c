/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04expander_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:01:44 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/05/05 10:42:17 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief takes a string s as input and checks if it contains
/// the character $. 
/// @param s 
/// @return 1 if $ is found in the string, and 0 otherwise.
int	dollar_in_str(char *s)
{
	while (*s)
	{
		if (*s == '$')
			return (1);
		s++;
	}
	return (0);
}

/// @brief  returns a string representation of the global
/// exit status variable g_exit_status.
/// @param  
/// @return *value
char	*get_exit_status(void)
{
	char	*value;

	value = ft_itoa(g_exit_status);
	if (!value)
		return (NULL);
	return (value);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

char	*find_envp_value(t_envp *env_lst, char *var_name)
{
	while (env_lst != NULL)
	{
		if (ft_strcmp(env_lst->envp_key, var_name) == 0)
			return (env_lst->envp_value);
		env_lst = env_lst->next;
	}
	return (NULL);
}
