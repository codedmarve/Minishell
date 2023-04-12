// char	*exit_or_dollar(char c, int *i)
// {
// 	char	*value;

// 	value = NULL;
// 	if (c == '?')
// 	{
// 		value = ft_itoa(exit_status);
// 	}
// 	else if (c == ' ' || c == '\0')
// 	{
// 		value = malloc(2 * sizeof(char));
// 		value[0] = '$';
// 		value[1] = '\0';
// 	}
// 	*i = *i + 1;
// 	return (value);
// }

// void	copy_rest(char *s, char *temp, int *i, int *t)
// {
// 	if (s[*i] == '\'')
// 	{
// 		temp[*t] = s[*i];
// 		*t = *t + 1;
// 		*i = *i + 1;
// 		while (s[*i] != '\'')
// 		{
// 			temp[*t] = s[*i];
// 			*t = *t + 1;
// 			*i = *i + 1;
// 		}
// 	}
// 	temp[*t] = s[*i];
// 	*t = *t + 1;
// 	*i = *i + 1;
// }

// char	*get_name(char *s, int i)
// {
// 	int		j;
// 	char	*name;

// 	j = 0;
// 	name = ft_calloc((i + 2), sizeof(char));
// 	// if (!name)
// 	// {
// 	// }
// 	while (j < i - 1)
// 	{
// 		name[j] = s[j];
// 		j++;
// 	}
// 	name[j] = '=';
// 	return (name);
// }

// char	*get_new_temp(char *temp, char *value, char *s)
// {
// 	char	*new_temp;

// 	new_temp = ft_strjoin(temp, value);
// 	// new_temp = strjoin_err(temp, value);
// 	free(temp);
// 	temp = ft_calloc((ft_strlen(s) + ft_strlen(value) + 1), sizeof(char));
// 	// if (!temp)
// 	// free(value);
// 	ft_strcpy(temp, new_temp);
// 	// free(new_temp);
// 	return (temp);
// }

// int	find_variable(char *s, char **value)
// {
// 	int		i;
// 	char	*name;

// 	i = 1;
// 	name = NULL;
// 	if (s[i] == '?' || s[i] == ' ' || s[i] == '\0')
// 		*value = exit_or_dollar(s[i], &i);
// 	else
// 	{
// 		i += find_end(&s[i], " <>|\"'$");
// 		name = get_name(&s[1], i);
// 		if (!name)
// 			return (i);
// 		*value = getenv(name);
// 		free(name);
// 	}
// 	return (i);
// }

// char *expander(char *input)
// {
// 	char *exp;
// 	char *value = NULL;
// 	int i = 0;
// 	int j = 0;

// 	exp = ft_calloc(ft_strlen(input), sizeof(char) + 1);
// 	//if !exp
// 	while (input[i])
// 	{
// 		if (input[i] == '$')
// 		{
// 			exp[j] = '\0';
// 			i += find_variable(&input[i], &value);
// 			j += ft_strlen(value);
// 			exp = get_new_temp(exp, value, input);
// 		}
// 		else
// 			copy_rest(input, exp, &i, &j);
// 	}
// 	return (exp);
// }