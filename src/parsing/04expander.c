/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04expander.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:01:50 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/05/09 14:16:03 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t add_exit_status_size(size_t *i)
{
    char *exit_status = get_exit_status();
    size_t exit_status_size = ft_strlen(exit_status);
    free(exit_status);
    *i += 1;
    return exit_status_size;
}

size_t add_single_dollar_size(size_t *i)
{
    *i += 1;
    return 1;
}

size_t add_env_var_size(size_t *i, char *token, t_data *data)
{
    char *var_name;
    char *env_var_value;
    size_t var_len = 0;
    size_t result;

    while (ft_isalnum(token[*i + var_len + 1]))
        var_len++;
    var_name = ft_substr(token, *i + 1, var_len);
    env_var_value = find_envp_value(data->env_lst, var_name);
    *i += var_len;
    if (env_var_value)
        result = ft_strlen(env_var_value);
    else
        result = 0;
    free(var_name);
    return result;
}

size_t calculate_expanded_token_size(char *token, t_data *data)
{
    size_t expanded_size = 0;
    size_t i;

    for (i = 0; token[i] != '\0'; i++)
    {
        if (token[i] == '$' && token[i + 1] == '?')
            expanded_size += add_exit_status_size(&i);
        else if (token[i] == '$' && token[i + 1] == '$')
            expanded_size += add_single_dollar_size(&i);
        else if (token[i] == '$' && (ft_isalnum(token[i + 1]) || token[i + 1] == '_'))
            expanded_size += add_env_var_size(&i, token, data);
        else
            expanded_size += 1;
    }
    return expanded_size;
}

char	*expand_token(char *token, t_data *data)
{
	char	*exp;
	t_idx	idx;
	size_t expanded_size;

	expanded_size = calculate_expanded_token_size(token, data);
    exp = malloc(expanded_size + 1); 
	// if ! exp
	idx.i = 0;
	idx.j = 0;
	while (token[idx.i] != '\0')
	{
		if (token[idx.i] == '$')
		{
			if (token[idx.i + 1] && token[idx.i + 1] == '?')
				init_exit_status(&exp, &idx);
			else if (token[idx.i + 1] && token[idx.i + 1] == '$')
				init_single_dollar(&exp, &idx);
			else if (token[idx.i + 1] && (ft_isalnum(token[idx.i + 1]) || token[idx.i + 1] == '_'))
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

// char	*expand_token(char *token, t_data *data)
// {
// 	char	*exp;
// 	t_idx	idx;

// 	exp = malloc(MAX_TOKEN_SIZE);
// 	// if ! new
// 	idx.i = 0;
// 	idx.j = 0;
// 	while (token[idx.i] != '\0')
// 	{
// 		if (token[idx.i] == '$')
// 		{
// 			if (token[idx.i + 1] == '?')
// 				init_exit_status(&exp, &idx);
// 			else if ( token[idx.i + 1] == '$')
// 				init_single_dollar(&exp, &idx);
// 			else if (ft_isalnum(token[idx.i + 1]) || token[idx.i + 1] == '_')
// 				init_env_var(&exp, &idx, token, data);
// 			else
// 				copy_token_char(&exp, &idx, token[idx.i++]);
// 		}
// 		else
// 			copy_token_char(&exp, &idx, token[idx.i++]);
// 	}
// 	exp[idx.j] = '\0';
// 	return (exp);
// }

/// @brief  loops through a linked list of tokens 
/// and expands any token that contains a dollar sign. 
///
/// If the token has single quotes around it, the dollar sign is not expanded. 
/// @param token_lst 
void	expand_token_lst(t_data *data)
{
	t_token	*tmp;
	char	*expanded_string; // NEW!!!!!!
	
	tmp = data->token_lst;
	// while (tmp != NULL)
	// {
	// 	if (tmp->quote_type != S_Q && dollar_in_str(tmp->string))
	// 		tmp->string = expand_token(tmp->string, data);
	// 	tmp = tmp->next;
	// }
	while (tmp != NULL)
	{
	//	if (dollar_in_expandable_str(tmp->string, tmp->quote_type))
		if (tmp->quote_type != S_Q && dollar_in_str(tmp->string))
		{
			expanded_string = expand_token(tmp->string, data);
			if (expanded_string != NULL)
			{
				free(tmp->string);
				tmp->string = expanded_string;
			}
		}
		tmp = tmp->next;
	}
}
