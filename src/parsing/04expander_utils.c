/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04expander_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:01:44 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/05/04 15:01:46 by dgoremyk         ###   ########.fr       */
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
