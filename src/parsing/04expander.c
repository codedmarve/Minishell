/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04expander.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:01:50 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/05/05 15:31:49 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_exit_status(char **new_ptr, t_idx *idx);
void	init_single_dollar(char **new_ptr, t_idx *idx);
void	expand_remainder(char **new_ptr, t_idx *idx, char *token, t_data *data);
char	*create_var_from_token(char *token, t_idx *idx);
void	copy_env_var_value(char **new_ptr, t_idx *idx, char *env_var);
void	init_env_var(char **new_ptr, t_idx *idx, char *token, t_data *data);
void	copy_token_char(char **new_ptr, t_idx *idx, char c);

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

void	expand_remainder(char **new_ptr, t_idx *idx, char *token, t_data *data)
{
	int	len;

	len = ft_strlen(token);
	while (token[idx->i] == '$' && idx->i < len)
	{
		if (token[idx->i + 1] == '?')
			init_exit_status(new_ptr, idx);
		else if (token[idx->i + 1] == '$')
			init_single_dollar(new_ptr, idx);
		else if (ft_isalnum(token[idx->i + 1]) || token[idx->i + 1] == '_')
			init_env_var(new_ptr, idx, token, data);
		else
			copy_token_char(new_ptr, idx, token[idx->i++]);
	}
}

char	*create_var_from_token(char *token, t_idx *idx)
{
	char	*var;
	int		var_len;

	var = malloc(ft_strlen(token) + 1);
	// if !var
	var_len = 0;
	while (ft_isalnum(token[idx->i]))
	{
		var[var_len++] = token[idx->i];
		idx->i++;
	}
	if (var_len == 0)
	{
		free(var);
		return (NULL);
	}
	var[var_len] = '\0';
	return (var);
}

void	copy_env_var_value(char **new_ptr, t_idx *idx, char *env_var)
{
	ft_strcpy(&(*new_ptr)[idx->j], env_var);
	idx->j += ft_strlen(env_var);
}

void	init_env_var(char **new_ptr, t_idx *idx, char *token, t_data *data)
{
	char	*var;
	char	*env_var;

	idx->i++;
	var = create_var_from_token(token, idx);
	if (!var)
		return ;

	env_var = find_envp_value(data->env_lst, var);
	if (env_var != NULL)
		copy_env_var_value(new_ptr, idx, env_var);
	expand_remainder(new_ptr, idx, token, data);
	idx->i += ft_strlen(var);
	free(var);
}

void	copy_token_char(char **new_ptr, t_idx *idx, char c)
{
	(*new_ptr)[(idx->j)++] = c;
}

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


// char	*expand_exit_status(char *exp, t_idx *idx)
// {
// 	char	*exit_status;

// 	exit_status = get_exit_status();
// 	if (!exit_status)
// 		return (NULL);
// 	ft_strcpy(&exp[idx->j], exit_status);
// 	idx->j += ft_strlen(exit_status);
// 	idx->i++;
// 	free(exit_status);
// 	return (exp);
// }

// char	*expand_env_var(char *exp, t_idx *idx, char *token, t_data *data)
// {
// 	char	var_name[MAX_TOKEN_SIZE];
// 	int		var_len;
// 	char	*var_value;

// 	var_len = 0;
// 	while (ft_isalnum(token[idx->i + 1 + var_len]) || token[idx->i + 1 + var_len] == '_')
// 		var_len++;
// 	ft_strncpy(var_name, &token[idx->i + 1], var_len);
// 	var_name[var_len] = '\0';
// 	var_value = find_envp_value(data->env_lst, var_name);
// 	if (var_value)
// 	{
// 		while (*var_value)
// 			exp[idx->j++] = *var_value++;
// 	}
// 	idx->i += var_len + 1;
// 	return (exp);
// }

// char	*expand_single_char(char *exp, t_idx *idx, char c)
// {
// 	exp[idx->j++] = c;
// 	idx->i++;
// 	return (exp);
// }

// char	*expand_token(char *token, t_data *data)
// {
// 	char	*exp;
// 	t_idx	idx;

// 	exp = malloc(MAX_TOKEN_SIZE);

// 	idx.i = 0;
// 	idx.j = 0;
// 	while (token[idx.i] != '\0')
// 	{
// 		if (token[idx.i] == '$')
// 		{
// 			if (token[idx.i + 1] == '?')
// 				exp = expand_exit_status(exp, &idx);
// 			else if (token[idx.i + 1] == '$')
// 				exp = expand_single_char(exp, &idx, token[idx.i++]);
// 			else if (ft_isalnum(token[idx.i + 1]) || token[idx.i + 1] == '_')
// 				exp = expand_env_var(exp, &idx, token, data);
// 			else
// 				exp = expand_single_char(exp, &idx, token[idx.i++]);
// 		}
// 		else
// 			exp = expand_single_char(exp, &idx, token[idx.i++]);
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
