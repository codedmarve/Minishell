/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04expander_init1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:01:38 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/05/09 15:03:34 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_exit_status(char **new_ptr, t_idx *idx)
{
	char	*exit_status;

	exit_status = get_exit_status();
	ft_strcpy(&(*new_ptr)[idx->j], exit_status);
	idx->j += ft_strlen(exit_status);
	free(exit_status);
	idx->i += 2;
}

/// @brief function replaces PID expansion => displays $ instead of $$
/// @param new_ptr 
/// @param idx 
void	init_single_dollar(char **new_ptr, t_idx *idx)
{
	(*new_ptr)[(idx->j)++] = '$';
	idx->i += 2;
}

// void	expand_remainder(char **new_ptr, t_idx *idx, char *token, t_data *data)
// {
// 	int	len;

// 	len = ft_strlen(token);
// 	while (token[idx->i] == '$' && idx->i < len)
// 	{
// 		if (token[idx->i + 1] == '?')
// 			init_exit_status(new_ptr, idx);
// 		else if (token[idx->i + 1] == '$')
// 			init_single_dollar(new_ptr, idx);
// 		else if (ft_isalnum(token[idx->i + 1]) || token[idx->i + 1] == '_')
// 			init_env_var(new_ptr, idx, token, data);
// 		else
// 			copy_token_char(new_ptr, idx, token[idx->i++]);
// 	}
// }

void	copy_token_char(char **new_ptr, t_idx *idx, char c)
{
	(*new_ptr)[(idx->j)++] = c;
}
