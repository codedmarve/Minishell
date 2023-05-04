/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04expander_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:01:38 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/05/04 15:01:41 by dgoremyk         ###   ########.fr       */
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

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		s1++;
        s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

char	*find_envp_value(t_envp *env_lst, const char *var_name)
{
	while (env_lst != NULL)
	{
		if (ft_strcmp(env_lst->envp_key, var_name) == 0)
			return (env_lst->envp_value);
		env_lst = env_lst->next;
	}
	return (NULL);
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
