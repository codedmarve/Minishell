/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04expander.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:01:50 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/05/04 15:01:53 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_token(char *token, t_data *data)
{
	char	*exp;
	t_idx	idx;

	exp = malloc(MAX_TOKEN_SIZE);
	// if ! new
	idx.i = 0;
	idx.j = 0;
	while (token[idx.i] != '\0')
	{
		if (token[idx.i] == '$')
		{
			if (token[idx.i + 1] == '?')
				init_exit_status(&exp, &idx);
			else if (token[idx.i + 1] == '$')
				init_single_dollar(&exp, &idx);
			else if (ft_isalnum(token[idx.i + 1]) || token[idx.i + 1] == '_')
				init_env_var(&exp, &idx, token, data);
			else
				copy_token_char(&exp, &idx, token[idx.i++]);
		}
		else
			copy_token_char(&exp, &idx, token[idx.i++]);
	}
	exp[idx.j] = '\0';
	return (exp);
}

/// @brief  loops through a linked list of tokens 
/// and expands any token that contains a dollar sign. 
///
/// If the token has single quotes around it, the dollar sign is not expanded. 
/// @param token_lst 
void	expand_token_lst(t_data *data)
{
	t_token	*tmp;

	tmp = data->token_lst;
	while (tmp != NULL)
	{
		if (tmp->quote_type != S_Q && dollar_in_str(tmp->string))
			tmp->string = expand_token(tmp->string, data);
		tmp = tmp->next;
	}
}
