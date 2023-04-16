
#include "../../includes/minishell.h"

/// @brief function takes a string as input and 
/// returns the index of the first non-space character in the string.
/// @param str 
/// @return index of the first non-space character in the string.
int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}

/// @brief  This function takes a string and a quote character as input and
/// returns the index of the first character after the end of the quoted string.
/// @param str 
/// @param quote 
/// @return the value of 'i' plus 1 to skip the closing quote character.
int	skip_quotes(char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i] != quote)
		i++;
	return (i + 1);
}

/// @brief takes a string and an array of possible separators as input and
/// returns the idx of the 1st occurrence of any of the separators in the str.
/// @param str 
/// @param possible_sep 
/// @return idx of the first occurrence of any of the separators in the string.
int	find_end(char *str, char *possible_sep)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (possible_sep[j])
		{
			if (str[i] == possible_sep[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}
