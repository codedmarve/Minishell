
#include "../../includes/minishell.h"

int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}

int	skip_quotes(char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i] != quote)
		i++;
	return (i + 1);
}

/*
take two strings and compare them. 
ifin the first str the occurence of char from second str
is found,
return index of that occurence. 

Else, return the end of the string.
Useful for counting word length.
str -  string to search through
possible_sep -  string to compare from
*/

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
