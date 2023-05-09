
// char	*expand_exit_status(char *exp, t_idx *idx)
// {
// 	char	*exit_status;

// 	exit_status = get_exit_status();
// 	if (!exit_status)
// 		return (NULL);
// 	ft_strcpy(&exp[idx->j], exit_status);
// 	idx->j += ft_strlen(exit_status);
// 	free(exit_status);
// 	idx->i += 2;
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

//////////////////////////////////////////////////////////////////////