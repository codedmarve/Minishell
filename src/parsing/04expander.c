
#include "../../includes/minishell.h"

/// @brief checks if string contains $ char
/// @param s 
/// @return 1 if $ found
int dollar_in_str(char *s)
{
	while (*s)
	{
		if (*s == '$')
			return (1);
		s++;
	}
	return (0);
}

/// @brief cheks if current char can belong to env varialbe
/// @param c 
/// @return 
int	env_var_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

/// @brief takes exit status from global variable,
/// saves it i a string *value
/// @param  
/// @return *value
char	*exit_status(void)
{
	char	*value;

	value = ft_itoa(g_exit_status);
	if (!value)
		return (NULL);
	return (value);
}

/// @brief FUNCTION SHOULD BE ADDED!
/// @param token 

/// commented out stuff - it s not working, WHY??????
void	expand_token(char **token)
{
	// char *new;

	// new = ft_calloc(1000, sizeof(char));
	// new[0] = 'a';
	// new[1] = '\0';
	// free(token);
	// *token = new;
	printf("EXPAND THIS: %s\n", *token);
	// return ;
}

void	expand_token_lst(t_token **token_lst)
{
	t_token	*tmp;

	tmp = *token_lst;
	while (tmp != NULL)
	{
		if (tmp->quote_type != S_Q && dollar_in_str(tmp->string))
			expand_token(&tmp->string);
		tmp = tmp->next;
	}
}
