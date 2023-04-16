
#include "../../includes/minishell.h"

/// @brief checks if string contains $ char
/// @param s 
/// @return 1 if $ found
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

/// @brief takes exit status from global variable,
/// saves it i a string *value
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
