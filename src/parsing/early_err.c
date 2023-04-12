
#include "../../includes/minishell.h"

// check behavior of redirection!


int	early_err(t_data *data)
{
	char	*input;

	input = data->input;
	if ((spaces_err(input) == -1)
		|| (quotes_err(input) == -1)
		|| (pipes_err(input) == -1)
		|| (spec_char_err(input) == -1)
		|| (redirection_err(input) == -1))
		return (-1);
	return (0);
}

