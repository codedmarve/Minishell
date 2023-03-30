
#include "../../includes/minishell.h"

static int	ft_isspace(char c)
{
	return ((c == ' ' || c == '\f'
			|| c == '\r' || c == '\t' || c == '\v'));
}

void	unify_spaces(char **input)
{
	char	*new;
	int		i;
	int		j;
	char	*tmp;

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
	quotes_reset(); // reset for using this check in next function
	new[j] = '\0';
	tmp = ft_strtrim(new, " "); //malloc, remove left, right spaces
	*input = ft_strdup(tmp);
	free(new);
	free(tmp);
}

void	remove_extra_spaces(char **input)
{
	char	*new;
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	j = 0;
	new = ft_strdup(*input);
	while ((*input)[++i])
	{
		if (quotes_are_closed((*input)[i]) && (*input)[i] == ' '
			&& (*input)[i + 1] && (*input)[i + 1] == ' ')
			continue ;
		new[j++] =(*input)[i];
	}
	quotes_reset();
	new[j] = '\0';
	tmp = ft_strtrim(new, " ");
	*input = ft_strdup(tmp);
	free(new);
	free(tmp);
}

void manipulate_input(char **input)
{
	// printf("INPUT: START%sEND\n", *input);
	// *input = ft_strtrim(*input, " \f\n\t\r\v");
	unify_spaces(input);
	remove_extra_spaces(input);
	// printf("CLEANED INPUT2: START%sEND\n", *input);
}