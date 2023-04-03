
#include "../../includes/minishell.h"

static int	ft_isspace(char c)
{
	return ((c == ' ' || c == '\f'
			|| c == '\r' || c == '\t' || c == '\v'));
}

/* 
all ISSPACE chars will become SPACE char

then uses STRTRIM to cut leading and closing spaces
*/
void	unify_spaces(char **input)
{
	char	*new;
	int		i;
	int		j;
	char	*tmp; // for a quick usage to use strtrim

	i = -1;
	j = 0;
	new = ft_strdup(*input); //malloc and copy
	// printf("new was created: %s\n", new);
	while ((*input)[++i])
	{
		if (quotes_are_closed((*input)[i]) && ft_isspace((*input)[i]))
		{
			new[j++] = ' ';
			continue ;
		}
		new[j++] = (*input)[i];
	}
	quotes_default(); // reset for using this check in next function
	new[j] = '\0';
	tmp = ft_strtrim(new, " "); //malloc, remove left, right spaces
	*input = ft_strdup(tmp);
	free(new);
	free(tmp);
}

/* removes SPACES which occure more then 1 time in a row */
void	remove_extra_spaces(char **input)
{
	char	*new;
	int		i;
	int		j;

	i = -1;
	j = 0;
	new = ft_strdup(*input);
	while ((*input)[++i])
	{
		if (quotes_are_closed((*input)[i]) && (*input)[i] == ' '
			&& (*input)[i + 1] && (*input)[i + 1] == ' ')
			continue ;
		new[j++] = (*input)[i];
	}
	quotes_default();
	new[j] = '\0';
	*input = ft_strdup(new);
	free(new);
}

void manipulate_input(char **input)
{
	// printf("INPUT: START%sEND\n", *input);
	unify_spaces(input);
	remove_extra_spaces(input);
	// printf("CLEANED INPUT2: START%sEND\n", *input);
}
